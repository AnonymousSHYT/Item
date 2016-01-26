#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <stdlib.h>
#include <string>

#include "Substrate.h"

#define LOG_TAG "item"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))

enum CreativeItemCategory {
	
};

class Item {
public:
	char filler[60];
	
	Item(std::string const&, short);
	
	virtual ~Item();
	void setIcon(std::string const&, int);
	void setCategory(CreativeItemCategory);
	static void initItems();
	static void initCreativeItems();
	static void addCreativeItem(short, short);
	static Item* mItems[4096];
};

static void (*Item$initItems_real)();
static void Item$initItems_hook() {
	Item$initItems_real();
	
	Item* manzana = new Item("manzana", 500 - 256);
	manzana->setIcon("apple", 0);
	manzana->setCategory((CreativeItemCategory) 3);
	Item::mItems[500] = manzana;
}

static void (*Item$initCreativeItems_real)();
static void Item$initCreativeItems_hook() {
	Item$initCreativeItems_real();
	
	Item::addCreativeItem(500, 0);
}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	MSHookFunction((void*) &Item::initItems, (void*) &Item$initItems_hook, (void**) &Item$initItems_real);
	MSHookFunction((void*) &Item::initCreativeItems, (void*) &Item$initCreativeItems_hook, (void**) &Item$initCreativeItems_real);
	return JNI_VERSION_1_2;
}
