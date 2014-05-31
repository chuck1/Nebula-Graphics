#ifndef __NEBULA_UI_OBJECT_TEXTVIEW_HPP__
#define __NEBULA_UI_OBJECT_TEXTVIEW_HPP__

#include <Nebula/Graphics/GUI/Object/Base.hh>

namespace Neb {
	namespace Graphics {
		namespace GUI {
			namespace Object {
				/** \brief %textview
				 * Display and optionally edit text
				 */
				class textview:
					public Neb::Graphics::GUI::Object::Base
				{
					public:
						textview();
						void			clear_label();
						virtual void		draw();

						//int			key(int, int, int, int);
						//int			key_down(int);
						//virtual int		enter();

						virtual int		key_fun(int,int,int,int);
						virtual int		mouse_button_fun(int,int,int);
						//virtual void		connect();

				};
			}
		}
	}
}

#endif
