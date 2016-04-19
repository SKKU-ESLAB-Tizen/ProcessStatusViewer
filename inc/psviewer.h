/*
 * psviewer.h
 * Author: Gyeonghwan Hong
 */

#ifndef PSVIEWER_H_
#define PSVIEWER_H_

#include <app.h>
#include <system_settings.h>
#include <Elementary.h>
#include <efl_extension.h>
#include <dlog.h>

#if !defined(PACKAGE)
#define PACKAGE "skku.ospractice.psviewer"
#endif

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "psviewer"

/* App Evas Objects: It contains Evas objects, which is main layout of the application */
typedef struct app_evas_objs {
	Evas_Object *mWindow;
	Evas_Object *mConformant;
	Evas_Object *mNaviFrame;
	Evas_Object *mBaseLayout;
	Evas_Object *mSidePanel;
	Evas_Object *mSidePanelList;
	Evas_Object *mGenList;
} app_eobjs_s;

#endif /* PSVIEWER_H_ */
