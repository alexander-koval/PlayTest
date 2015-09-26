#ifndef __EFFECTPRESETS_H__
#define __EFFECTPRESETS_H__

#pragma once

#include "Particles/ParticleEffect.h"

/// ����������� ������� ������, ������� ��� ������������.
class EffectPresets {
public:
	void UploadEffect(const std::string& name);
	void ReleaseEffect(const std::string& name);

	bool LoadEffects(const std::string& filename, const std::string& group = "Common");

	bool SaveToXml(const std::string& filename);
	bool SaveToBin(const std::string& filename);
	
	/// �������� �������� �������� ������
	void UnloadEffectsGroup(const std::string& group);

	/// ���������� �������� �������, ���� ����, ����� ���������� NULL
	ParticleEffectPtr FindEffect(const std::string &name) const;
	/// ��������� ������
	ParticleEffectPtr CreateEffect(const std::string& name) const;
	ParticleEffectPtr CreateEffect(const std::string& name, const FPoint& position) const;
	
	std::vector<ParticleEffectPtr>& GetEffects() { return _effects; }

    void Shutdown();

private:
	bool LoadFromXml(const std::string& filename, const std::string& group);
	bool LoadFromBin(const std::string& filename, const std::string& group);

private:
	typedef std::vector<ParticleEffectPtr> Effects;
	Effects _effects;

	typedef std::vector<Render::Sheet*> Sheets;
	std::shared_ptr<Sheets> current_sheets;
};

extern EffectPresets effectPresets;

#endif // __EFFECTPRESETS_H__
