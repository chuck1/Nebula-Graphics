#ifndef __GRU_ACTOR_PARENT_H__
#define __GRU_ACTOR_PARENT_H__

#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Galaxy-Standard/shared.hpp>

#include <Nebula/Util/parent.hpp>

#include <Nebula/Scene/Util/Cast.hh>

#include <Nebula/Actor/__base.hpp>
#include <Nebula/Actor/Util/Types.hh>
#include <Nebula/Actor/Util/Cast.hh>

#include <Nebula/Graphics/material.hh>
#include <Nebula/Graphics/mesh.hh>

#include <Nebula/Core/Pose.hh>

namespace neb {
	namespace Actor {
		namespace Util {
			/** @brief @Parent
			 * abstract class for parent of an @Actor
			 */
			class Parent:
				public Neb::Util::parent<neb::actor::__base>,
				virtual public Neb::Core::Pose,
				virtual public Neb::Scene::Util::Cast,
				virtual public Neb::Actor::Util::Cast
			{
				public:
					Parent();
					virtual ~Parent() {}

					virtual void				init();
				public:
					Neb::Scene::Base_s			getScene();
			};
		}
	}
}

#endif

