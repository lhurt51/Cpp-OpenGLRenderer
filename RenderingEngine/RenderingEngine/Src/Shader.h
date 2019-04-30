#pragma once

#include <map>
#include <vector>
#include <string>

#include "Utils\ReferenceCounter.h"
#include "Utils\Math\MathUtils.h"
#include "Material.h"
#include "Transform.h"
#include "Camera.h"

class RenderingEngine;
class DirectionalLight;
class PointLight;
class SpotLight;

class TypedData
{

	std::string m_name;
	std::string m_type;

public:

	TypedData(const std::string& name, const std::string& type) :
		m_name(name), m_type(type)
	{}

	inline const std::string& GetName() const { return m_name; }
	inline const std::string& GetType() const { return m_type; }

};

struct UniformStruct
{

	std::string				m_name;
	std::vector<TypedData>	m_memberNames;

public:

	UniformStruct(const std::string& name, const std::vector<TypedData>& memberNames) : m_name(name), m_memberNames(memberNames)
	{}

	inline const std::string& GetName() const { return m_name; }
	inline const std::vector<TypedData>& GetMemberNames() const { return m_memberNames; }

};

class ShaderData : public ReferenceCounter
{

	static int							s_supportedGLSLLevel;
	int									m_program;
	std::vector<int>					m_shaders;
	std::vector<std::string>			m_uniformNames;
	std::vector<std::string>			m_uniformTypes;
	std::map<std::string, unsigned int>	m_uniformMap;

public:

	ShaderData(const std::string& fileName);
	virtual ~ShaderData();

	inline int GetProgram() const { return m_program; }
	inline const std::vector<int>& GetShader() const { return m_shaders; }
	inline const std::vector<std::string>& GetUniformNames() const { return m_uniformNames; }
	inline const std::vector<std::string>& GetUniformTypes() const { return m_uniformTypes; }
	inline const std::map<std::string, unsigned int>& GetUniformMap() const { return m_uniformMap; }

private:

	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void AddProgram(const std::string& text, int type);

	void AddAllAttributes(const std::string& vertexShaderText, const std::string& attributeKeyword);
	void AddShaderUniforms(const std::string& shaderText);
	void AddUniform(const std::string& uniformName, const std::string& uniformType, const std::vector<UniformStruct>& structs);
	void CompileShader() const;
	void ConvertVertexShaderToGLSL150(std::string* shaderText);
	void ConvertFragmentShaderToGLSL150(std::string* shaderText);

};

class Shader
{
	
	static std::map<std::string, ShaderData*> s_resourceMap;

	ShaderData* m_shaderData;
	std::string m_fileName;

public:

	Shader(const std::string& fileName);
	Shader(const Shader& other);
	virtual ~Shader();

	void Bind() const;
	virtual void UpdateUniforms(const Transform& transform, const Material& material, const RenderingEngine& renderingEngine, const Camera& camera) const;

	void SetUniformi(const std::string& uniformName, int value) const;
	void SetUniformf(const std::string& uniformName, float value) const;
	void SetUniformMatrix4f(const std::string& uniformName, const Matrix4f& value) const;
	void SetUniformVector3f(const std::string& uniformName, const Vector3f& value) const;

private:

	void SetUniformDirectionalLight(const std::string& uniformName, const DirectionalLight& value) const;
	void SetUniformPointLight(const std::string& uniformName, const PointLight& value) const;
	void SetUniformSpotLight(const std::string& uniformName, const SpotLight& value) const;

};

