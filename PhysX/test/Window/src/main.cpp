#include <glm/gtc/matrix_transform.hpp>

#include <Nebula/App/Base.hh>
#include <Nebula/Actor/Base.hh>
#include <Nebula/Util/wrapper.hpp>
#include <Nebula/Graphics/Context/Window.hpp>
#include <Nebula/Graphics/environ/two.hpp>
#include <Nebula/Graphics/environ/three.hpp>
#include <Nebula/Graphics/GUI/Object/terminal.hh>
#include <Nebula/Graphics/Light/Spot.hh>
#include <Nebula/Scene/Local.hh>
#include <Nebula/Shape/Box.hh>
#include <Nebula/Shape/empty.hpp>
#include <Nebula/Actor/RigidDynamic/Local.hh>

#include <PhysX/free.hpp>
#include <PhysX/app/base.hpp>
#include <PhysX/core/scene/local.hpp>

sp::shared_ptr<neb::gfx::context::window>		create_context_two(sp::shared_ptr<neb::gfx::window::base> window) {

	auto context = sp::make_shared<neb::gfx::context::window>(window);
	
	window->insert(context);

	context->environ_ = sp::make_shared<neb::gfx::environ::two>(/*context*/);

	context->init();
	
	//auto context = window->cii< neb::gfx::context::window, sp::shared_ptr<neb::gfx::window::base> >(window);
	
	
	

	return context;
}
sp::shared_ptr<neb::gfx::context::window>		create_context_three(sp::shared_ptr<neb::gfx::window::base> window) {
	assert(window);
	
	auto context = sp::make_shared<neb::gfx::context::window>(window);
	assert(context);
	
	window->insert(context);
	
	
	
	auto environ = sp::make_shared<neb::gfx::environ::three>(/*context*/);
	environ->init();
	
	context->environ_ = environ;
	
	
	
	context->init();
	
	//auto context = window->cii< neb::gfx::context::window, sp::shared_ptr<neb::gfx::window::base> >(window);
	
	assert(environ->view_);
	
	environ->view_->connect(window);

	return context;
}

sp::shared_ptr<neb::gfx::gui::layout::base>	create_layout(
		sp::shared_ptr<neb::gfx::window::base> window,
		sp::shared_ptr<neb::gfx::context::window> context) {

	auto app = neb::app::base::global();
	
	//auto layout = app->neb::gfx::gui::layout::util::parent::cii<neb::gfx::gui::layout::base, neb::App::base>(app);


	auto layout = sp::make_shared<neb::gfx::gui::layout::base>(app);

	app->neb::gfx::gui::layout::util::parent::insert(layout);

	
	context->environ_->drawable_ = layout;

	layout->connect(window);

	// object
	auto term = sp::make_shared<neb::gfx::gui::object::terminal>();

	layout->insert(term);

	term->init();

	return layout;
}
sp::shared_ptr<neb::core::actor::rigiddynamic::local>		create_actor(sp::shared_ptr<neb::scene::local> scene) {

	/*
	auto actor = sp::make_shared<neb::core::actor::rigiddynamic::local>(scene);
	
	scene->insert(actor);

	actor->init();
	*/

	auto actor = scene->cii<neb::core::actor::rigiddynamic::local, sp::shared_ptr<neb::scene::local>>(scene);



	// shape	
	auto shape = sp::make_shared<neb::core::shape::Box>(actor);
	
	
	actor->neb::core::shape::util::parent::insert(shape);
	//actor->insert(shape);
	
	
	shape->init();
	
	return actor;	
}
sp::shared_ptr<neb::core::actor::rigiddynamic::local>		create_actor2(sp::shared_ptr<neb::scene::local> scene) {
	auto actor = sp::make_shared<neb::core::actor::rigiddynamic::local>(scene);
	
	scene->insert(actor);
	
	actor->init();
	
	// shape	
	/*
	auto shape = sp::make_shared<neb::core::shape::empty>(actor);
	
	actor->neb::core::shape::util::parent::insert(shape);
	
	shape->init();
	*/
	auto shape = actor->neb::core::shape::util::parent::cii< neb::core::shape::empty, sp::shared_ptr<neb::core::actor::rigiddynamic::local> >(actor);
	
	// light
	auto light = sp::make_shared<neb::Light::Point>(shape);
	
	shape->neb::Light::util::parent::insert(light);
	
	light->init();
	
	// another light
	
	light = sp::make_shared<neb::Light::Point>(shape);
	
	shape->neb::Light::util::parent::insert(light);
	
	light->init();

	light->pos_ = vec3(10,0,0);

	return actor;	
}
sp::shared_ptr<neb::scene::local>			create_scene(
		sp::shared_ptr<neb::gfx::context::window> context) {

	std::cout << "4\n";

	auto app = neb::app::base::global();
	assert(app);
	
	std::cout << "5\n";

	auto scene = sp::make_shared<phx::core::scene::local>(app);
	assert(scene);

	std::cout << "6\n";

	app->neb::scene::util::parent::insert(scene);

	std::cout << "7\n";

	scene->init();
	
	std::cout << "8\n";

	// actors
	auto actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,0,-5));
	
	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,0,5));
	
	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,-5,0));

	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(0,5,0));

	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(-5,0,0));

	actor = create_actor(scene);
	actor->pose_ = glm::translate(actor->pose_, vec3(5,0,0));



	auto actor2 = create_actor2(scene);




	
	context->environ_->drawable_ = scene;

	return scene;
}

int			main() {

	phx::init();

	auto app = phx::app::base::global();

	// window	
	auto window = sp::make_shared<neb::gfx::window::base>();

	app->neb::gfx::window::util::parent::insert(window);

	window->init();

	// context
	auto context1 = create_context_three(window);
	auto context2 = create_context_two(window);

	std::cout << "1\n";

	// drawable
	auto scene = create_scene(context1);

	std::cout << "2\n";

	auto layout = create_layout(window, context2);

	std::cout << "3\n";

	// loop

	app->loop();

}



