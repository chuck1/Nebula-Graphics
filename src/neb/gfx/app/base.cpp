#include <neb/fnd/except/base.hpp>

#include <neb/gfx/core/scene/base.hpp>
#include <neb/gfx/core/actor/base.hpp>
#include <neb/gfx/core/shape/base.hpp>
#include <neb/gfx/core/light/Base.hpp>
#include <neb/gfx/app/base.hpp>
#include <neb/gfx/Viewport.hpp>

typedef neb::gfx::app::Base THIS;

/*
std::weak_ptr<THIS>			THIS::initialize()
{
	assert(!g_app_);
*
	typedef THIS T;

	auto app = std::shared_ptr<T>(new T());

	g_app_ = app;

	//app->neb::app::__core::init();
	
	app->neb::gfx::app::__gfx::init();
	app->neb::gfx::app::__gfx_glsl::__init();

	return app;
	*

	throw neb::fnd::except::NotImplemented();

	return std::weak_ptr<THIS>();
}
*/
void					THIS::init(parent_t * const & p)
{
	setParent(p);

	// gfx
	gal::tmp::VerbosityRegister::reg<neb::gfx::window::Base>("neb gfx window base");
	gal::tmp::VerbosityRegister::reg<neb::gfx::context::base>("neb gfx context base");
	gal::tmp::VerbosityRegister::reg<neb::gfx::environ::base>("neb gfx environ base");

	
	gal::tmp::VerbosityRegister::reg<neb::gfx::core::scene::base>("neb gfx core scene base");
	gal::tmp::VerbosityRegister::reg<neb::gfx::core::actor::base>("neb gfx core actor base");
	gal::tmp::VerbosityRegister::reg<neb::gfx::core::shape::base>("neb gfx core shape base");
	gal::tmp::VerbosityRegister::reg<neb::gfx::core::light::Base>("neb gfx core light base");

	gal::tmp::VerbosityRegister::reg<neb::gfx::camera::view::Base>("neb gfx camera view base");
	gal::tmp::VerbosityRegister::reg<neb::gfx::camera::view::Ridealong>("neb gfx camera view ridealong");

	gal::tmp::VerbosityRegister::reg<neb::gfx::camera::proj::Base>("neb gfx camera proj base");

	gal::tmp::VerbosityRegister::reg<neb::fnd::glsl::program::Base>("neb gfx glsl program base");

	gal::tmp::VerbosityRegister::reg<neb::gfx::Viewport>("neb gfx viewport");

	neb::gfx::app::draw::__init();
	neb::gfx::app::glfw::__init();
	neb::gfx::app::glsl::__init();

}
void					THIS::__init()
{
}
double					THIS::get_time()
{
	return glfwGetTime();
}
void					THIS::release()
{
	neb::gfx::app::draw::release();
	//neb::gfx::app::__gfx_glsl::release();
}
void					THIS::__release()
{
}
void					THIS::step(gal::etc::timestep const & ts)
{
	//neb::fnd::app::__base::step(ts);
	//neb::fnd::app::Base::__step(ts);
	
	neb::gfx::app::draw::step(ts);
	//neb::gfx::app::__gfx_glsl::step(ts);
}
/*
void					THIS::loop()
{
	while(!getParent()->flag_.any(neb::fnd::app::util::flag::E::SHOULD_RELEASE)) {
		::std::cout << "loop1" << ::std::endl;
		ts_.step(glfwGetTime());
		step(ts_);
	}
}
*/
/*void					THIS::render()
{
	neb::gfx::app::glfw::render();
}*/
void		THIS::update()
{
	glfwPollEvents();

	neb::gfx::app::glfw::update_joysticks();
}



