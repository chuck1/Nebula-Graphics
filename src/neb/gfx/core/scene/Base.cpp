
#include <neb/core/math/geo/polyhedron.hh>

#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/camera/proj/base.hpp>
#include <neb/gfx/camera/view/Base.hh>
#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/RenderDesc.hpp>
#include <neb/gfx/texture.hpp>
#include <neb/gfx/util/log.hpp>

typedef neb::gfx::core::scene::base THIS;
typedef neb::core::core::actor::util::parent A;
typedef neb::gfx::glsl::program::base P;

void			THIS::__init(parent_t * const & p)
{
	LOG(lg, neb::gfx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	// graphics

	// use _M_programs._M_d3 as completion flag
	if(!_M_programs._M_d3)
	{
		// programs
		_M_programs._M_d3.reset(new neb::gfx::glsl::program::threed("3d"));
		_M_programs._M_d3->init();

		_M_programs._M_d3_HF.reset(new neb::gfx::glsl::program::threed("3d_HF"));
		_M_programs._M_d3_HF->init();

		_M_programs._M_d3_inst.reset(new neb::gfx::glsl::program::threed("3d_inst"));
		_M_programs._M_d3_inst->init();

		init_light();

		// meshes
		nc::math::geo::cuboid cube(1.0,1.0,1.0);

		meshes_.cuboid_.reset(new neb::gfx::mesh::instanced);
		meshes_.cuboid_->mesh_.construct(&cube);

		meshes_.cuboid_->instances_.reset(new neb::gfx::mesh::instanced::instances_type);
		meshes_.cuboid_->instances_->alloc(2048);

		unsigned int shadow_tex_size = 512;

		tex_shadow_map_ = std::make_shared<neb::gfx::texture>();
		tex_shadow_map_->init_shadow(
				shadow_tex_size,
				shadow_tex_size,
				std::shared_ptr<neb::gfx::context::base>());
	}
}
void			THIS::init_light()
{
	LOG(lg, neb::gfx::core::scene::sl, debug) << __PRETTY_FUNCTION__;

	if(!light_array_[0])
	{
		// light arrays
		light_array_[0].reset(new neb::gfx::glsl::uniform::light_array);
		light_array_[0]->alloc(32);

		light_array_[1].reset(new neb::gfx::glsl::uniform::light_array);
		light_array_[1]->alloc(32);
	}
}
void			THIS::draw(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	assert(desc.p);
	assert(desc.v);

	drawMesh(desc);
	drawMeshHF(desc);
	drawMeshInst(desc);
}
void			THIS::drawMesh(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// If program parameter is not NULL, use it and do not load lights.
	//
	// For rendering lights, use one of the programs owned by this, which contain persistent data for the lights.
	
	P* d3;

	if(desc.d3) {
		d3 = desc.d3;
	} else {
		assert(_M_programs._M_d3);
		d3 = _M_programs._M_d3.get();
	}

	assert(d3);

	d3->use();

	desc.p->load(d3);
	desc.v->load(d3);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(d3);

	// individual meshes
	auto la = [&] (A::map_type::pointer p) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(p);
		assert(actor);
		actor->draw(d3, neb::core::math::pose());
	};

	A::map_.for_each(la);

}
void			THIS::drawMeshHF(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	// If program parameter is not NULL, use it and do not load lights.
	//
	// For rendering lights, use one of the programs owned by this, which contain persistent data for the lights.

	P* p;

	if(desc.d3_HF) {
		p = desc.d3_HF;
	} else {
		assert(_M_programs._M_d3_HF);
		p = _M_programs._M_d3_HF.get();
	}

	assert(p);

	p->use();

	desc.p->load(p);
	desc.v->load(p);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(p);

	// individual meshes
	auto la = [&] (A::map_type::pointer ptr) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(ptr);
		assert(actor);
		actor->drawHF(p, neb::core::math::pose());
	};

	A::map_.for_each(la);

}
void			THIS::drawMeshInst(neb::gfx::RenderDesc const & desc)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	P* d3_inst;

	if(desc.d3_inst) {
		d3_inst = desc.d3_inst;
	} else {
		assert(_M_programs._M_d3);
		d3_inst = _M_programs._M_d3_inst.get();
	}

	assert(d3_inst);

	d3_inst->use();

	desc.p->load(d3_inst);
	desc.v->load(d3_inst);

	// lights
	assert(light_array_[0]);
	light_array_[0]->load_uniform(d3_inst);

	if(tex_shadow_map_) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(tex_shadow_map_->target_, tex_shadow_map_->o_);

		GLint loc = d3_inst->uniform_table_[neb::gfx::glsl::uniforms::TEX_SHADOW_MAP];
		neb::gfx::ogl::glUniform(loc, 0);
	}

	// meshes
	assert(meshes_.cuboid_);
	meshes_.cuboid_->draw(d3_inst);

}
void			THIS::drawDebug(
		neb::gfx::RenderDesc const & desc)
{
	auto app(neb::gfx::app::__gfx_glsl::global().lock());

	auto p = app->program_simple3_;
	p->use();

	desc.p->load(p.get());
	desc.v->load(p.get());

	// individual meshes
	auto la = [&] (A::map_type::pointer ptr) {
		auto actor = std::dynamic_pointer_cast<neb::gfx::core::actor::base>(ptr);
		assert(actor);
		actor->drawDebug(p.get(), neb::core::math::pose());
	};

	A::map_.for_each(la);

}
void			THIS::resize(int w, int h)
{
}

