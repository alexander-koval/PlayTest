#ifndef __BINDABLE_H__
#define __BINDABLE_H__

#pragma once

#include "Render/RenderTypes.h"

namespace Render {

class RenderDeviceGLES2;

///
/// ������� ����� ��� �������� (�������), ������� ����������� � �����������.
///
class Bindable : public RefCounter {
public:
	Bindable()
		: _filtering(FilteringType::Bilinear)
		, _address(AddressMode::Clamp)
		, _filteringDirty(true)
		, _addressDirty(true)
	{
	}

	virtual ~Bindable() = default;

	/// ���������� ��� ����������
	FilteringType GetFilteringType() const { return _filtering; }

	/// ������������� ��� ����������
	void SetFilteringType(FilteringType filtering) { _filtering = filtering; _filteringDirty = true; }

	/// ���������� ����� ���������
	AddressMode GetAddressMode() const { return _address; }

	/// ������������� ����� ���������
	void SetAddressMode(AddressMode address) { _address = address; _addressDirty = true; }

	/// ��������� ���������� ������� � �������������
	virtual bool Empty() const = 0;

	/// ��������� ������ � ����������� �����������
	virtual void Bind(int channel, int stageOp) = 0;

	/// ���������� ������������� ������� � ����������� ����������
	virtual const void* GetNativeHandle() const = 0;

	/// ���������� ��� �������
	virtual TextureType GetTextureType() const = 0;

private:
	friend class RenderDeviceGLES2;

	FilteringType _filtering;   ///< ��� ����������
	AddressMode _address;       ///< ����� ���������

	bool _filteringDirty;    ///< ��������� �� _filtering
	bool _addressDirty;	  ///< ��������� �� _address
};

typedef boost::intrusive_ptr<Bindable> BindablePtr;

} // namespace Render

#endif // __BINDABLE_H__
