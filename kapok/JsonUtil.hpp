#pragma once
#include <string>
#include <cstdint>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/document.h"
using namespace rapidjson;

#include "traits.hpp"
#include "Common.hpp"

class JsonUtil : NonCopyable
{
	typedef Writer<StringBuffer> JsonWriter;
public:

	JsonUtil() : m_writer(m_buf)
	{
	}

	template<typename T>
	void WriteJson(const char* key, T&& value)
	{
		m_writer.String(key);
		WriteValue(std::forward<T>(value));
	}

	template<typename T>
	void WriteJson(const string& key, T&& value)
	{
		m_writer.String(key.c_str());
		WriteValue(std::forward<T>(value));
	}

	void Reset()
	{
		m_writer.Reset(m_buf);
		m_buf.Clear();
	}

	void StartObject()
	{
		m_writer.StartObject();
	}

	void EndObject()
	{
		m_writer.EndObject();
	}

	void StartArray()
	{
		m_writer.StartArray();
	}

	void EndArray()
	{
		m_writer.EndArray();
	}

	void WriteValue(const char* val)
	{
		if (val == nullptr)
			m_writer.Null();
		else
			m_writer.String(val);
	}

	void ReadValue(char*& t, Value& val)
	{
		if (val.IsString())
			t = (char*)val.GetString();
		else
			t = nullptr;
	}

	void WriteValue(const string& val)
	{
		m_writer.String(val.c_str());
	}

	void ReadValue(string& t, Value& val)
	{
		if (val.IsString())
			t = val.GetString();
		else
			t = "";
	}

	void Parse(const char* json)
	{
		auto& r = m_doc.Parse<0>(json);
		if (r.HasParseError())
		{
			throw std::invalid_argument("json string parse failed");
		}
	}

	void Parse(const char* json, std::size_t length)
	{
		auto& r = m_doc.Parse<0>(json, length);
		if (r.HasParseError())
		{
			throw std::invalid_argument("json string parse failed");
		}
	}

	Document& GetDocument()
	{
		return m_doc;
	}

	void WriteValue(uint8_t val)
	{
		m_writer.Int(val);
	}

	void ReadValue(uint8_t& t, Value& val)
	{
		t = (uint8_t)val.GetInt();
	}

	void WriteValue(int8_t val)
	{
		m_writer.Int(val);
	}

	void ReadValue(int8_t& t, Value& val)
	{
		t = (int8_t)val.GetInt();
	}

	void WriteValue(int16_t val)
	{
		m_writer.Int(val);
	}

	void ReadValue(int16_t& t, Value& val)
	{
		t = (int16_t)val.GetInt();
	}

	void WriteValue(uint16_t val)
	{
		m_writer.Int(val);
	}

	void ReadValue(uint16_t& t, Value& val)
	{
		t = (uint16_t)val.GetInt();
	}

	void WriteValue(int val)
	{
		m_writer.Int(val);
	}

	void ReadValue(int& t, Value& val)
	{
		if (val.IsInt())
			t = val.GetInt();
		else
			t = 0;
	}

	void WriteValue(char val)
	{
		m_writer.Int(val);
	}

	void ReadValue(char& t, Value& val)
	{
		if (val.IsInt())
			t = (char)val.GetInt();
		else
			t = 0;
	}

	void WriteValue(uint32_t val)
	{
		m_writer.Uint(val);
	}

	void ReadValue(uint32_t& t, Value& val)
	{
		if (val.IsUint())
			t = val.GetUint();
		else
			t = 0;
	}

	void WriteValue(int64_t val)
	{
		m_writer.Int64(val);
	}

	void ReadValue(int64_t& t, Value& val)
	{
		if (val.IsInt64())
			t = val.GetInt64();
		else
			t = 0;
	}

	void WriteValue(uint64_t val)
	{
		m_writer.Uint64(val);
	}

	void ReadValue(uint64_t& t, Value& val)
	{
		if (val.IsUint64())
			t = val.GetUint64();
		else
			t = 0;
	}

	void WriteValue(double val)
	{
		m_writer.Double(val);
	}

	void ReadValue(double& t, Value& val)
	{
		if (val.IsDouble())
			t = val.GetDouble();
		else
			t = 0;
	}

	void WriteValue(float val)
	{
		m_writer.Double(static_cast<double>(val));
	}

	void ReadValue(float& t, Value& val)
	{
		if (val.IsDouble())
			t = static_cast<float>(val.GetDouble());
		else
			t = 0;
	}

	template<typename T>
	typename std::enable_if<std::is_same<T, bool>::value>::type WriteValue(T val)
	{
		m_writer.Bool(val);
	}

	//还要过滤智能指针的情况.
	template<typename T>
	typename std::enable_if<is_pointer_ext<T>::value>::type WriteValue(T val)
	{
		//不支持动态指针的原因是反序列化的时候涉及到指针的内存管理，反序列化不应该考虑为对象分配内存.
		throw std::invalid_argument("not surpport dynamic pointer");
	}

	void WriteNull()
	{
		m_writer.Null();
	}

	void ReadValue(bool& t, Value& val)
	{
		if (val.IsBool())
			t = val.GetBool();
		else
			t = 0;
	}

	const char* GetJosnText()
	{
		return m_buf.GetString();
	}

private:
	StringBuffer m_buf; //json字符串的buf.
	JsonWriter m_writer; //json写入器.
	Document m_doc;
};
