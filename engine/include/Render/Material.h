#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#pragma once

#include "Render/RenderTypes.h"
#include "Render/Bindable.h"
#include "Render/CombinedTexture.h"
#include "Render/ShaderProgram.h"
#include "Render/RenderDevice.h"

#include <array>

namespace Render {

///
/// �������� ��� ������������ ���������.
///
/// �������� � ���� ��������� ���� �������, ������ � ����� ����������.
///
class Material {
public:
	Material()
		: _blend(BlendMode::Alpha)
	{
	}

	Material(Bindable* tex, ShaderProgram* shader, BlendMode blend = BlendMode::Alpha)
		: _shader(shader), _blend(blend)
	{
		_bindables[0] = tex;
	}

	Material(Bindable* tex1, Bindable* tex2, ShaderProgram* shader, BlendMode blend = BlendMode::Alpha)
		: _shader(shader), _blend(blend)
	{
		_bindables[0] = tex1;
		_bindables[1] = tex2;
	}

	Material(Bindable* tex1, Bindable* tex2, Bindable* tex3, ShaderProgram* shader, BlendMode blend = BlendMode::Alpha)
		: _shader(shader), _blend(blend)
	{
		_bindables[0] = tex1;
		_bindables[1] = tex2;
		_bindables[2] = tex3;
	}

	Material(Bindable* tex1, Bindable* tex2, Bindable* tex3, Bindable* tex4, ShaderProgram* shader, BlendMode blend = BlendMode::Alpha)
		: _shader(shader), _blend(blend)
	{
		_bindables[0] = tex1;
		_bindables[1] = tex2;
		_bindables[2] = tex3;
		_bindables[3] = tex4;
	}

	Material(const Material&) = default;
	Material& operator=(const Material&) = default;

	friend bool operator==(const Material& lhs, const Material& rhs) {
		for (size_t i = 0; i < kMaxStages; ++i) {
			if (!AreBindablesEqual(lhs._bindables[i].get(), rhs._bindables[i].get()))
				return false;
		}

		if (lhs._shader != rhs._shader)
			return false;

		return lhs._blend == rhs._blend;
	}

	friend bool operator!=(const Material& lhs, const Material& rhs) {
		return !operator==(lhs, rhs);
	}

	size_t GetTextureCount() const {
		size_t result = 0;

		for (/**/; result < kMaxStages; ++result) {
			if (!_bindables[result])
				break;
		}

		return result;
	}

	Bindable* GetTexture(size_t i) const { Assert(i < kMaxStages); return i < kMaxStages ? _bindables[i].get() : 0; }

	ShaderProgram* GetShaderProgram() const { return _shader.get(); }

	BlendMode GetBlendMode() const { return _blend; }

	///
	/// ���������� ��������� ��� �������� ��������� � �����������
	///
	void Bind() const {
		int stage = 0;

		for (size_t i = 0; i < _bindables.size(); ++i) {
			if (!_bindables[i]) {
				break;
			}

			if (_bindables[i]->GetTextureType() == TextureType::CombinedTexture) {
				Assert(stage < kMaxStages - 1);
				_bindables[i]->Bind(stage, 0);
				// CombinedTexture �������� ��� ��������, ������� ��� ���������� � ����������� �������� ��� ����
				stage += 2;
			} else {
				Assert(stage < kMaxStages);
				_bindables[i]->Bind(stage++, 0);
			}
		}

		if (_shader)
			_shader->Bind();

		device.SetBlendMode(_blend);
	}

	///
	/// ��������� �� �������� ��������� � �����������, ������� �� ��������� � ������� ����������
	///
	void Bind(const Material& currentMaterial) const {
		int stage = 0;

		for (size_t i = 0; i < _bindables.size(); ++i) {
			if (!AreBindablesEqual(_bindables[i].get(), currentMaterial._bindables[i].get())) {
				if (_bindables[i]) {
					if (_bindables[i]->GetTextureType() == TextureType::CombinedTexture) {
						Assert(stage < kMaxStages - 1);
						_bindables[i]->Bind(stage, 0);
						// CombinedTexture �������� ��� ��������, ������� ��� ���������� � ����������� �������� ��� ����
						stage += 2;
					} else {
						Assert(stage < kMaxStages);
						_bindables[i]->Bind(stage++, 0);
					}
				} else {
					if (_bindables[i]->GetTextureType() == TextureType::CombinedTexture) {
						Assert(stage < kMaxStages - 1);
						device.Bind((Texture*)nullptr, stage++);
						device.Bind((Texture*)nullptr, stage++);
					} else {
						Assert(stage < kMaxStages);
						device.Bind((Texture*)nullptr, stage++);
					}
				}
			}
		}

		if (_shader != currentMaterial._shader) {
			if (_shader) {
				_shader->Bind();
			} else {
				// ���� �������� �� �������, ������, currentMaterial._shader != NULL
				currentMaterial._shader->Unbind();
			}
		}

		if (_blend != currentMaterial._blend)
			device.SetBlendMode(_blend);
	}

private:
	static bool AreBindablesEqual(const Bindable* tex1, const Bindable* tex2) {
		bool equal = tex1 == tex2;

		// ������ ���������� ����� ��������� �� ���� � ��� �� �����, �� ������ ���� ��� �� �������� � ������ ����
		if (!equal) {
			// ���� �� ������� ��������
			if (!tex1 || !tex2)
				return false;

			// �������� ������� ����
			if (tex1->GetTextureType() != tex2->GetTextureType())
				return false;

			// ��������� ������������� ������� ������ ����
			if (tex1->GetTextureType() == TextureType::CombinedTexture) {
				equal = ((CombinedTexture*)tex1)->GetColorTexture()->GetNativeHandle() == ((CombinedTexture*)tex2)->GetColorTexture()->GetNativeHandle()
					&& ((CombinedTexture*)tex1)->GetAlphaTexture()->GetNativeHandle() == ((CombinedTexture*)tex2)->GetAlphaTexture()->GetNativeHandle();
			} else {
				equal = tex1->GetNativeHandle() == tex2->GetNativeHandle();
			}
		}

		return equal;
	}

private:
	enum { kMaxStages = 4 };

	typedef std::array<BindablePtr, kMaxStages> Bindables;

	Bindables _bindables;
	ShaderProgramPtr _shader;
	BlendMode _blend;
};

} // namespace Render

#endif // __MATERIAL_H__
