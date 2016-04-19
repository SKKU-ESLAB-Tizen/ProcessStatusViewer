/*
 * common_ui.h
 */

#ifndef COMMON_UI_H_
#define COMMON_UI_H_

#include <Elementary.h>
#include <efl_extension.h>

Evas_Object* create_button(Evas_Object *parent, char *style, char *text);
Evas_Object* create_scroller(Evas_Object *parent);
Evas_Object* create_box(Evas_Object *parent);
Evas_Object* create_label(Evas_Object *parent, char *text);

#endif /* COMMON_UI_H_ */
