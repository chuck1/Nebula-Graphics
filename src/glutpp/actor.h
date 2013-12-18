#ifndef __GLUTPP_ACTOR_H__
#define __GLUTPP_ACTOR_H__
#include <memory>

#include <math/vec4.h>
#include <math/vec3.h>
#include <math/vec2.h>
#include <math/geo/polyhedron.h>
#include <math/transform.h>

#include <glutpp/texture.h>
//#include <glutpp/uniform.h>
//#include <glutpp/attribute.h>
#include <glutpp/material.h>


namespace glutpp
{
	struct file_header
	{
		GLint len_vertices_;
		GLint len_indices_;
	};

	struct vertex
	{
		void		print();

		math::vec4	position;
		math::vec3	normal;
		math::vec2	texcoor;
	};

	class window;
	class scene;
	namespace glsl
	{
		class program;
	}
	class actor
	{
		public:
			enum
			{
				VAO = 1 << 0
			};
			enum
			{
				NONE = 0,
			};

			actor();
			void		init(std::shared_ptr<scene>);
			std::shared_ptr<scene>	get_scene();
			
			void		construct(math::geo::polyhedron*);
			void		uniforms();
			int		save(char const *);
			int		load(char const *);
			void		init_buffer(std::shared_ptr<glutpp::glsl::program> p);
			void		model_load();
			void		model_unload();


			virtual void	draw();
			virtual void	render_reflection();

			
			int		i_;
			int		type_;


			//attribute		attrib_position_;
			//attribute		attrib_normal_;
			//attribute		attrib_texcoor_;
			//GLint location_image_;

			texture			texture_image_;

			//uniform			uniform_image_;

			GLuint			vbo_;
			GLuint			buffer_indices_;

			//math::mat44		model_;
			math::transform		pose_;
			math::vec3		s_;

			// draw data
			file_header		fh_;
			glutpp::vertex*		vertices_;
			GLushort*		indices_;

			material		material_front_;

			std::weak_ptr<scene>	scene_;
	};
}

#endif