
#include <gru/scene/desc.hpp>
#include <gru/scene/scene.hpp>


void glutpp::scene::addr::load(glutpp::scene::scene_s scene) {
	auto vec = std::get<0>(tup_);
	vec->vec_.clear();
	vec->vec_.push_back(scene->i());
}



