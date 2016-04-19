/*
 * common_ui.c
 * Author: Gyeonghwan Hong
 */
#include "common_ui.h"

/* Create button */
Evas_Object* create_button(Evas_Object *parent, char *style, char *text) {
	Evas_Object *button;

	button = elm_button_add(parent);
	if (style)
		elm_object_style_set(button, style);
	if (text)
		elm_object_text_set(button, text);
	evas_object_show(button);

	return button;
}

/* Create scroller */
Evas_Object* create_scroller(Evas_Object *parent) {
	Evas_Object *scroller;

	scroller = elm_scroller_add(parent);
	elm_scroller_policy_set(scroller, ELM_SCROLLER_POLICY_OFF,
			ELM_SCROLLER_POLICY_AUTO);
	evas_object_show(scroller);

	return scroller;
}

/* Create box */
Evas_Object* create_box(Evas_Object *parent) {
	Evas_Object *box;
	box = elm_box_add(parent);
	evas_object_show(box);

	return box;
}

/* Create label */
Evas_Object* create_label(Evas_Object *parent, char *text) {
	Evas_Object *label;
	label = elm_label_add(parent);

	elm_object_text_set(label, text);
	evas_object_show(label);

	return label;
}
