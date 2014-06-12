#ifndef NEBULA_SCENE_UTIL_PARENT_HH
#define NEBULA_SCENE_UTIL_PARENT_HH

#include <Galaxy-Standard/map.hpp>

#include <Nebula/Core/Pose.hh>

#include <Nebula/Scene/Util/Types.hh>
#include <Nebula/Scene/Base.hh>
#include <Nebula/Util/parent.hpp>

namespace neb {
	namespace Scene {
		namespace Util {
			class Parent:
				virtual public Neb::Util::parent<Neb::Scene::Base>,
				virtual public Neb::Core::Pose
			{
				public:
			};
		}
	}
}

#endif

