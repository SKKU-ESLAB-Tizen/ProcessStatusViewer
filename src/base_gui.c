/*
 * base_gui.c
 * Author: Gyeonghwan Hong
 */

#include "base_gui.h"
#include "psviewer.h"
#include "common_ui.h"
#include "side_panel.h"
#include "total_list_naviframe_item.h"

/* Windows delete request callback */
static void win_delete_request_cb(void *data, Evas_Object *obj,
		void *event_info) {
	ui_app_exit();
}

/* Naviframe pop callback */
static Eina_Bool naviframe_pop_cb(void *data, Elm_Object_Item *it) {
	/* Don't pop the last view but hide window */
	app_eobjs_s *appEobjs = data;
	elm_win_lower(appEobjs->mWindow);
	return EINA_FALSE;
}

/* Side panel button clicked callback */
static void side_panel_button_clicked_cb(void *data, Evas_Object * obj,
		void *event_info) {
	app_eobjs_s *appEobjs = data;
	if (!elm_object_disabled_get(appEobjs->mSidePanel))
		elm_panel_toggle(appEobjs->mSidePanel);
}

/* List clicked callback */
static void list_clicked_cb(void *data, Evas_Object *obj, void *event_info) {
	app_eobjs_s *appEobjs = data;
	Elm_Object_Item *it = (Elm_Object_Item *) elm_list_selected_item_get(obj);
	if (it == NULL)
		return;
	elm_object_item_part_text_set(
			elm_naviframe_top_item_get(appEobjs->mNaviFrame), NULL,
			elm_object_item_part_text_get(it, "default"));
	elm_list_item_selected_set(it, EINA_FALSE);

	elm_panel_toggle(appEobjs->mSidePanel);
}

/* Lisk back callback */
static void list_back_cb(void *data, Evas_Object *obj, void *event_info) {
	Evas_Object *panel = data;
	elm_panel_hidden_set(panel, EINA_TRUE);
}

/* Total process list callback */
void total_process_list_cb(void *data, Evas_Object *obj, void *event_info) {
	/* Add your application logic. */
}

/* Process tree callback */
void process_tree_cb(void *data, Evas_Object *obj, void *event_info) {
	/* Add your application logic. */
}

/*******************************************************************************/

/* Create base GUI */
void create_base_gui(app_eobjs_s *app_eobjs) {
	Evas_Object *sidePanelBtn, *background;
	Elm_Object_Item *naviFrameItem;

	/* Window */
	app_eobjs->mWindow = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_conformant_set(app_eobjs->mWindow, EINA_TRUE);
	elm_win_autodel_set(app_eobjs->mWindow, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(app_eobjs->mWindow)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(app_eobjs->mWindow,
				(const int *) (&rots), 4);
	}

	evas_object_smart_callback_add(app_eobjs->mWindow, "delete,request",
			win_delete_request_cb,
			NULL);

	/* Conformant */
	app_eobjs->mConformant = elm_conformant_add(app_eobjs->mWindow);
	evas_object_size_hint_weight_set(app_eobjs->mConformant, EVAS_HINT_EXPAND,
	EVAS_HINT_EXPAND);
	elm_win_indicator_mode_set(app_eobjs->mWindow, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(app_eobjs->mWindow, ELM_WIN_INDICATOR_OPAQUE);
	elm_win_resize_object_add(app_eobjs->mWindow, app_eobjs->mConformant);
	evas_object_show(app_eobjs->mConformant);

	/* Indicator BG */
	background = elm_bg_add(app_eobjs->mConformant);
	elm_object_style_set(background, "indicator/headerbg");
	elm_object_part_content_set(app_eobjs->mConformant,
			"elm.swallow.indicator_bg", background);
	evas_object_show(background);

	/* Main View */
	app_eobjs->mBaseLayout = create_main_view(app_eobjs);
	elm_object_content_set(app_eobjs->mConformant, app_eobjs->mBaseLayout);

	/* Naviframe */
	app_eobjs->mNaviFrame = elm_naviframe_add(app_eobjs->mBaseLayout);
	eext_object_event_callback_add(app_eobjs->mNaviFrame, EEXT_CALLBACK_BACK,
			eext_naviframe_back_cb, app_eobjs);
	elm_object_part_content_set(app_eobjs->mBaseLayout, "elm.swallow.content",
			app_eobjs->mNaviFrame);
	evas_object_show(app_eobjs->mNaviFrame);

	/* Naviframe item */
	/* Initial naviframe item is total list naviframe item. */
	naviFrameItem = create_total_list_naviframe_item(app_eobjs);
	elm_naviframe_item_pop_cb_set(naviFrameItem, naviframe_pop_cb,
			app_eobjs);

	/* left panel toggle button */
	sidePanelBtn = create_button(app_eobjs->mNaviFrame, "naviframe/drawers",
	NULL);
	evas_object_smart_callback_add(sidePanelBtn, "clicked",
			side_panel_button_clicked_cb, app_eobjs);
	elm_object_item_part_content_set(naviFrameItem, "title_left_btn",
			sidePanelBtn);

	/* Show window after base gui is set up */
	evas_object_show(app_eobjs->mWindow);
}

/* Create main view */
Evas_Object* create_main_view(app_eobjs_s *app_eobjs) {
	Evas_Object *layout;
	/* Drawer layout */
	layout = create_base_layout(app_eobjs->mConformant);

	/* Side panel */
	app_eobjs->mSidePanel = create_side_panel(layout);
	elm_object_part_content_set(layout, "elm.swallow.left",
			app_eobjs->mSidePanel);

	/* Side panel list */
	app_eobjs->mSidePanelList = create_side_panel_list(app_eobjs->mSidePanel);
	evas_object_size_hint_weight_set(app_eobjs->mSidePanelList,
	EVAS_HINT_EXPAND,
	EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(app_eobjs->mSidePanelList, EVAS_HINT_FILL,
	EVAS_HINT_FILL);
	evas_object_smart_callback_add(app_eobjs->mSidePanelList, "selected",
			list_clicked_cb, app_eobjs);
	eext_object_event_callback_add(app_eobjs->mSidePanelList,
			EEXT_CALLBACK_BACK, list_back_cb, app_eobjs->mSidePanel);
	elm_object_content_set(app_eobjs->mSidePanel, app_eobjs->mSidePanelList);

	return layout;
}

/* Create base layout */
Evas_Object* create_base_layout(Evas_Object *parent_eobj) {
	Evas_Object *layout;
	layout = elm_layout_add(parent_eobj);
	elm_layout_theme_set(layout, "layout", "drawer", "panel");
	evas_object_show(layout);

	return layout;
}
