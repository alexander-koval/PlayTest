#ifndef __CONTENTPROVIDER_H__
#define __CONTENTPROVIDER_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <RefCounter.h>

#include "ModelNode.h"

#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#endif

namespace SceneGraph {

///
/// Базовый класс для провайдеров контента.
///
struct ContentProvider : public RefCounter
{
	typedef boost::intrusive_ptr<ContentProvider> HardPtr;
		
	virtual ModelNode* LoadModel(const std::string& filename) = 0;
		/// Загружает модель из файла
};

} // namespace SceneGraph


#if defined(__clang__) || defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

#endif // __CONTENTPROVIDER_H__
