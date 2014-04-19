#include <math/free.hpp>


#include <gru/scene/raw.hpp>
#include <gru/scene/scene.hpp>

glutpp::scene::raw::raw():
	flag_(0)
{
	GLUTPP_DEBUG_0_FUNCTION;
	//i_ = -1;
}
void glutpp::scene::raw::load(tinyxml2::XMLElement* element) {
	GLUTPP_DEBUG_0_FUNCTION;
	
	flag_ = math::xml_parse_int(element->FirstChildElement("flags"), 0);
	
	gravity_ = math::xml_parse_vec3(element->FirstChildElement("gravity"), math::vec3<double>(0,0,0));
}
void glutpp::scene::raw::load(glutpp::scene::scene_s scene) {
	GLUTPP_DEBUG_0_FUNCTION;

	*this = scene->raw_;
}


