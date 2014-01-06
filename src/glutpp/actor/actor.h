#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>
#include <vector>
#include <map>

#include <gal/flag.h>
#include <gal/network/message.h>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/geo/polyhedron.h>
#include <math/transform.h>

#include <glutpp/config.h>
#include <glutpp/texture.h>
#include <glutpp/material.h>
#include <glutpp/shape/shape.h>

namespace glutpp
{
	namespace actor
	{
		class actor: public std::enable_shared_from_this<actor>, public gal::flag
		{
			public:
				typedef std::shared_ptr<gal::network::message> msg_type;
				
				enum flag
				{
					SHOULD_DELETE = 1 << 0
				};

				actor(
						glutpp::actor::desc_shared,
						std::shared_ptr<glutpp::scene::scene>,
						glutpp::actor::actor_shared = glutpp::actor::actor_shared());
				void			i(int);
				math::mat44		get_pose();
				
				std::shared_ptr<scene::scene>	get_scene();

				void			draw(glutpp::window::window_shared);
				void			load_lights(int&);

				virtual void		cleanup();
				virtual void		release();

				
				msg_type			serialize();
				glutpp::actor::desc_shared	desc_generate();
				
				//virtual void	render_reflection();

				
				
				
				glutpp::actor::desc_shared	desc_;

				std::weak_ptr<scene::scene>	scene_;
				std::weak_ptr<actor>		actor_;
			protected:
				glutpp::shape::shape_map	shapes_;
				glutpp::actor::actor_map	actors_;

		};
	}
}

#endif
