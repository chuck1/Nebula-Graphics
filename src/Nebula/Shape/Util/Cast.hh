#ifndef NEBULA_SHAPE_UTIL_CAST_HH
#define NEBULA_SHAPE_UTIL_CAST_HH

#include <Nebula/Util/Shared.hh>

#include <Nebula/Shape/Util/Types.hh>

namespace Neb {
        namespace Shape {
                namespace Util {
                        class Cast: virtual public Neb::Util::Shared {
                                public:
                                        Neb::Actor::Base_s                              isActorBase();
        				Neb::Actor::Actor_s                             isActorActor();
        				Neb::Actor::RigidActor_s			isActorRigidActor();
        				Neb::Actor::RigidBody::RigidBody_s		isActorRigidBody();
                        };
                }
        }
}

#endif