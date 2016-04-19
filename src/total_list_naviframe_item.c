/*
 * total_process_list.c
 * Author: Gyeonghwan Hong
 */

#include "total_list_naviframe_item.h"
#include "base_gui.h"
#include "detailed_box.h"

/* GenList callbacks START */
static void genlist_del_cb(void *data, Evas_Object *obj EINA_UNUSED) {
	/* Unrealized callback can be called after this. */
	/* Accessing list_item_eobjs_s can be dangerous on unrealized callback. */
	list_item_eobjs_s *listItemEobjs = data;
	free(listItemEobjs);
}

static char *
genlist_text_get_cb(void *data, Evas_Object *obj, const char *part) {
	list_item_eobjs_s *listItemEobjs = data;
	const Elm_Genlist_Item_Class *itemClass = elm_genlist_item_item_class_get(
			listItemEobjs->mItem);
	char buf[1024];

	/* TODO: Retrieve process information from list item */
	int pid = listItemEobjs->pid;
	char* process_name = listItemEobjs->process_name;

	/***********************************************/

	/* TODO: Update genlist item text */
	if (!strcmp(itemClass->item_style, "type1")) {
		if (!strcmp(part, "elm.text")) {
			snprintf(buf, 1023, "(pid %d) %s", pid, process_name);
			return strdup(buf);
		} else if (!strcmp(part, "elm.text.sub")) {
			snprintf(buf, 1023, "%s", "Additional Information");
			return strdup(buf);
		} else if (!strcmp(part, "elm.text.sub.end")) {
			snprintf(buf, 1023, "%s", "Side");
			return strdup(buf);
		}
	}
	/**********************************/

	return NULL;
}

static void genlist_loaded_cb(void *data EINA_UNUSED,
		Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED) {

}

static void genlist_realized_cb(void *data EINA_UNUSED,
		Evas_Object *obj EINA_UNUSED, void *event_info) {
	/* If you need, you can get item's data. */
	/*
	 Elm_Object_Item *objectItem = event_info;
	 list_item_eobjs_s *listItemEobjs = elm_object_item_data_get(objectItem);
	 */
}

static void genlist_longpressed_cb(void *data EINA_UNUSED,
		Evas_Object *obj EINA_UNUSED, void *event_info) {
	/* If you need, you can get item's data. */
	/*
	 Elm_Object_Item *objectItem = event_info;
	 list_item_eobjs_s *listItemEobjs = elm_object_item_data_get(objectItem);
	 */
}

/* Genlist item selected callback */
static void genlist_selected_cb(void *data EINA_UNUSED,
		Evas_Object *obj EINA_UNUSED, void *event_info) {
	Elm_Object_Item *objectItem = event_info;
	list_item_eobjs_s *listItemEobjs = elm_object_item_data_get(objectItem);

	/* Remove highlight from item */
	elm_genlist_item_selected_set(listItemEobjs->mItem, EINA_FALSE);

	create_detailed_box(listItemEobjs);
}
/* GenList callbacks END */

/* Create Genlist */
#define NUM_OF_ITEMS 50
Evas_Object* create_genlist(app_eobjs_s *app_eobjs, Evas_Object *parent_eobj) {
	Evas_Object *genlist;
	Elm_Object_Item *it;
	int n_items = NUM_OF_ITEMS;
	int index;

	/* Create item class */
	Elm_Genlist_Item_Class *itemClass = elm_genlist_item_class_new();

	itemClass->item_style = "type1";
	itemClass->func.text_get = genlist_text_get_cb;
	itemClass->func.del = genlist_del_cb;

	genlist = elm_genlist_add(parent_eobj);

	elm_object_style_set(genlist, "handler");
	elm_scroller_single_direction_set(genlist,
			ELM_SCROLLER_SINGLE_DIRECTION_HARD);

	/* HOMOGENEOUS MODE
	 If item height is same when each style name is same, Use homogeneous mode. */
	elm_genlist_homogeneous_set(genlist, EINA_TRUE);

	/* COMPRESS MODE
	 For the Mobile view, because it has full window, compress mode should be used. */
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);

	/* Add Smart Callback */
	evas_object_smart_callback_add(genlist, "realized", genlist_realized_cb,
	NULL);
	evas_object_smart_callback_add(genlist, "loaded", genlist_loaded_cb, NULL);
	evas_object_smart_callback_add(genlist, "longpressed",
			genlist_longpressed_cb,
			NULL);

	/* TODO: Retrieve process information from kernel */
	int pid = 1;
	char process_name[100] = "process_name";
	/**************************************************/

	for (index = 0; index < n_items; index++) {
		list_item_eobjs_s *listItemEobjs = calloc(sizeof(list_item_eobjs_s), 1);
		listItemEobjs->mAppEobjs = app_eobjs;

		/* TODO: Set process information of list item */
		listItemEobjs->pid = pid;
		strncpy(listItemEobjs->process_name, process_name, 100);
		pid++; /* Remove this line */

		/***********************************************/

		it = elm_genlist_item_append(genlist, /* genlist object */
		itemClass, /* item class */
		listItemEobjs, /* item class user data */
		NULL, /* parent item */
		ELM_GENLIST_ITEM_NONE, /* item type */
		genlist_selected_cb, /* select smart callback */
		listItemEobjs); /* smart callback user data */
		listItemEobjs->mItem = it;
	}
	elm_genlist_item_class_free(itemClass);
	evas_object_show(genlist);

	return genlist;
}

Elm_Object_Item* create_total_list_naviframe_item(app_eobjs_s *app_eobjs) {
	/* Genlist */
	app_eobjs->mGenList = create_genlist(app_eobjs, app_eobjs->mBaseLayout);
	return elm_naviframe_item_push(app_eobjs->mNaviFrame,
				"Total Process List", NULL, NULL, app_eobjs->mGenList, NULL);
}
