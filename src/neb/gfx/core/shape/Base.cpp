#include <glm/gtx/transform.hpp>

#include <gal/stl/map.hpp>

#include <gal/log/log.hpp>

#include <neb/core/util/debug.hpp>

#include <neb/gfx/util/io.hpp>
#include <neb/gfx/app/__gfx_glsl.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/core/light/point.hpp>
#include <neb/gfx/core/light/spot.hpp>
#include <neb/gfx/core/light/directional.hpp>
#include <neb/gfx/glsl/attrib.hh>
#include <neb/gfx/glsl/uniform/scalar.hpp>
#include <neb/gfx/glsl/program/threed.hpp>
#include <neb/gfx/util/log.hpp>
#include <neb/gfx/mesh/tri1.hpp>
#include <neb/gfx/mesh/instanced.hpp>
#include <neb/gfx/opengl/uniform.hpp>

#include <neb/core/math/geo/polygon.hpp>

typedef neb::gfx::core::shape::base THIS;

THIS::base()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
THIS::~base() {}
void					THIS::init(neb::fnd::core::shape::util::parent * const & p)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;

	setParent(p);

	if(!neb::fnd::app::Base::is_valid()) return;

	createMesh();
}
void					THIS::release()
{
	neb::fnd::core::shape::base::release();
}
void					THIS::step(gal::etc::timestep const & ts)
{

	//material_front_.step(ts);
}
void					THIS::v_set_pose_data(neb::fnd::math::pose const & gpose)
{
	LOG(lg, neb::gfx::core::shape::sl, debug) << __PRETTY_FUNCTION__;
	LOG(lg, neb::gfx::core::shape::sl, debug) << gpose.mat4_cast();

	neb::fnd::core::shape::base::__set_pose_data(gpose);

	if(mesh_slot_) {
		auto model = gpose.mat4_cast() * glm::scale(scale_);
		
		mesh_slot_->set<0>(model);
		LOG(lg, neb::gfx::core::shape::sl, debug) << "slot " << mesh_slot_->index_;
	}
}
/*void					THIS::setPose(neb::fnd::math::pose const & pose)
{
	LOG(lg, neb::gfx::core::shape::sl, debug) << __PRETTY_FUNCTION__;
	
	auto npose = pose * pose_;

	neb::gfx::core::light::util::parent::setPose(npose);
}*/
void					THIS::draw(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	auto npose = pose * pose_;
	
	draw_elements(p, npose);
}
void			THIS::drawHF(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
}
void			THIS::model_load(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	glm::mat4 space = pose.mat4_cast() * glm::scale(scale_);

	auto v = p->get_uniform_table_value(neb::gfx::glsl::uniforms::MODEL);

	assert(v != -1);

	neb::gfx::ogl::glUniform(v, space);
}
void			THIS::draw_elements(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;

	assert(p);

	if(mesh_) {
		mesh_->drawElements(p, pose, scale_);
	} else {
		draw_legacy(p, pose);
	}
}
void			THIS::drawDebug(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__ << " " << this;
	
	assert(p);
	
	if(mesh_)
	{
		mesh_->drawDebug(p, pose, scale_);
	}
}
std::weak_ptr<neb::fnd::core::light::base>		THIS::createLightPoint()
{
	auto self(std::dynamic_pointer_cast<neb::fnd::core::shape::base>(shared_from_this()));

	typedef neb::gfx::core::light::point L;

	auto light = std::shared_ptr<L>(new L());

	neb::fnd::core::light::util::parent::insert(light);

	light->init(this);

	return light;
}
std::weak_ptr<neb::fnd::core::light::base>		THIS::createLightSpot(glm::vec3 d)
{

	auto self(std::dynamic_pointer_cast<neb::fnd::core::shape::base>(shared_from_this()));

	typedef neb::gfx::core::light::spot L;

	auto light = std::shared_ptr<L>(new L(), gal::stl::deleter<L>());

	light->spot_direction_ = d;

	neb::fnd::core::light::util::parent::insert(light);

	light->init(this);

	return light;
}
std::weak_ptr<neb::fnd::core::light::base>		THIS::createLightDirectional(glm::vec3 d)
{

	auto self(std::dynamic_pointer_cast<neb::fnd::core::shape::base>(shared_from_this()));

	typedef neb::gfx::core::light::directional L;
	
	auto light = std::shared_ptr<L>(new L(), gal::stl::deleter<L>());

	light->pose_.pos_ = d;

	neb::fnd::core::light::util::parent::insert(light);

	light->init(this);

	return light;
}
void						THIS::createMesh()
{
	LOG(lg, neb::gfx::sl, debug) << __PRETTY_FUNCTION__;
}
void						THIS::draw_legacy(
		neb::fnd::glsl::program::Base const * const & p,
		neb::fnd::math::pose const & pose)
{
}



