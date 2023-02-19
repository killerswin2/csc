#include "json.hpp"
#include "../commands.hpp"
#include <ostream>
#include <istream>
#include <fstream>
#include <future>

#ifdef _WIN32 
#define WIN32_LEAN_AND_MEAN
#include <windows.h> 
#include <Shlobj.h>
#define INITKNOWNFOLDERS
#include <Knownfolders.h>
#endif // !_WIN32 

static sqf_script_type game_data_json_type;
static sqf_script_type game_data_json_array_type;

const sqf_script_type& game_data_json::type() const
{
	return game_data_json_type;
}

serialization_return game_data_json::serialize(param_archive& ar)
{
	game_data::serialize(ar);
	size_t entryCount;
	if (ar._isExporting) entryCount = jsonObject.size();
	return serialization_return::no_error;
}


game_data* create_game_data_json(param_archive* arch)
{
	auto data = new game_data_json;
	if (arch)
	{
		data->serialize(*arch);
	}
	return data;
}


game_value create_json_object()
{
	return game_value(new game_data_json());
}

void json_game_data::json::pre_start()
{
	auto codeType = intercept::client::host::register_sqf_type("JSONHASHMAP"sv, "jsonHashMap"sv, "hashmap for json stuff", "jsonHashMap"sv, create_game_data_json);
	game_data_json_type = codeType.second;

	Commands& commands = Commands::get();
	commands.addCommand("createJsonObject", "create a json object", userFunctionWrapper<create_json_object>, codeType.first);

	//commands.addCommand("","");
	//commands.addCommand("count", "returns number of keys");
	//commands.addCommand("count", "returns number elements with key");
	//commands.addCommand("accept", "checks if the input is valid JSON");
	//commands.addCommand("array", "creates JSON array given the list of data");
	//commands.addCommand("back", "returns the last element in the json object");
	//commands.addCommand("clear", "clears the contents of the json object");
	//commands.addCommand("contains","checks whether an element exists in the JSON object with the Key");
	//commands.addCommand("dump", "serialization for JSON values");
	//commands.addCommand("emplace", "inserts a new element into a JSON object in-place");
	//commands.addCommand("emplaceBack", "creates a JSON value from the Args to the end of object");
	//commands.addCommand("empty", "checks if the JSON object has no elements");
	//commands.addCommand("erase", "removes element from JSON by key");
	//commands.addCommand("erase", "removes element from JSON element range");
	//commands.addCommand("erase", "removes an element from a JSON array by index");
	//commands.addCommand("find", "finds an element in a JSON object with a key that was passed");
	//commands.addCommand("fromBJdata", "deserializes a given input using BJData");
	//commands.addCommand("fromBson", "deserializes a given input using BSON");
	//commands.addCommand("fromCbor", "deserializes a given input using CBOR");
	//commands.addCommand("fromMSGpack", "deserializes a given input using MSGPACK");
	//commands.addCommand("fromUBjson", "deserializes a given input using UBJSON");
	//commands.addCommand("front", "returns the first element in the json object");
	//commands.addCommand("insert", "inserts element into array before pos");
	//commands.addCommand("insert", "inserts range of elements into array");
	//commands.addCommand("insert", "inserts range of elements into JSON");
	//commands.addCommand("isArray", "returns if and only if the JSON value is an array");
	//commands.addCommand("isBinary", "returns if and only if the JSON value is an binary array");
	//commands.addCommand("isBool", "returns if and only if the JSON value is a bool");
	//commands.addCommand("isNumber", "returns if and only if the JSON value is a number");
	//commands.addCommand("isNumberFloat", "returns if and only if the JSON value is a float");
	//commands.addCommand("isNumberInteger", "returns if and only if the JSON value is a integer");
	//commands.addCommand("isNumberUnsigned", "returns if and only if the JSON value is a unsigned int");
	//commands.addCommand("isObject", "returns if and only if the JSON value is a JSON object");
	//commands.addCommand("isPrimitive", "returns if and only if the JSON value is a primitive type");
	//commands.addCommand("isString", "returns if and only if the JSON value is a string");
	//commands.addCommand("isStructured", "returns if and only if the JSON value is a structured (object or array)");
	//commands.addCommand("meta", "returns JSON object meta information");
	//commands.addCommand("==", "compares two json objects and returns if equal")
	//commands.addCommand("isEqualTo","compares two json objects and returns if equal");
	//commands.addCommand("!=","");
	//commands.addCommand("<","");
	//commands.addCommand(">","");
	//commands.addCommand("<=","");
	//commands.addCommand(">=","");
	//commands.addCommand("parse","");
	//commands.addCommand("patch","");
	//commands.addCommand("patchInplace","");
	//commands.addCommand("pushBack","");
	//commands.addCommand("swap","");
	//commands.addCommand("toBJdata","");
	//commands.addCommand("toBson","");
	//commands.addCommand("toCbor","");
	//commands.addCommand("toMSGpack","");
	//commands.addCommand("toString","");
	//commands.addCommand("toUBjson","");
	//commands.addCommand("type","");
	//commands.addCommand("typeName","");
	//commands.addCommand("update","");
	//commands.addCommand("value","");




	//separator
	//commands.addCommand("getNested", "returns data from a nested object key", userFunctionWrapper<jsonHashGetNested>, game_data_type::ANY, codeType.first, game_data_type::ARRAY);
	//commands.addCommand("set", "set key value pair in hashmap", userFunctionWrapper<jsonHashSet>, game_data_type::NOTHING, codeType.first, game_data_type::ARRAY);
	//commands.addCommand("dumpToFile", "dumps json data to file", userFunctionWrapper<jsonDump>, game_data_type::NOTHING, codeType.first);
}

const sqf_script_type& game_data_json_array::type() const
{
	return game_data_json_array_type;
}

serialization_return game_data_json_array::serialize(param_archive& ar)
{
	game_data::serialize(ar);
	size_t entryCount;
	if (ar._isExporting) entryCount = jsonArray.size();
	return serialization_return::no_error;
}


game_data* create_game_data_json_array(param_archive* arch)
{
	auto data = new game_data_json;
	if (arch)
	{
		data->serialize(*arch);
	}
	return data;
}


game_value create_json_array()
{
	return game_value(new game_data_json_array());
}

//helper function that can be used to determine if the element can be json
bool canJson(const game_value& element)
{
	game_data* GameDataPointer = element.data.get();
	return (
		GameDataPointer->type() == game_data_json_type ||
		GameDataPointer->type() == game_data_json_array_type ||
		element.type() == game_data_array::type_def ||
		element.type() == game_data_string::type_def ||
		element.type() == game_data_number::type_def ||
		element.type() == game_data_bool::type_def
		);
}

void push_back_internal(const game_value& element, nlohmann::json& jsonArray)
{
	game_data* GameDataPointer = element.data.get();
	if (!canJson(element))
	{
		intercept::sqf::system_chat("Can't Json This");
	}

	//json data type
	if (GameDataPointer->type() == game_data_json_type)
	{
		intercept::sqf::system_chat("json data");
		auto jsonObjectPointer = static_cast<game_data_json*>(GameDataPointer);
		jsonArray.push_back(jsonObjectPointer->jsonObject);
		return;
	}
	// json array
	if (GameDataPointer->type() == game_data_json_array_type)
	{
		intercept::sqf::system_chat("json array");
		auto jsonObjectPointer = static_cast<game_data_json_array*>(GameDataPointer);
		jsonArray.push_back(jsonObjectPointer->jsonArray);
		return;
	}

	// string
	if (element.type() == game_data_string::type_def)
	{
		intercept::sqf::system_chat("RV string");
		auto gameDataStringPointer = static_cast<game_data_string*>(GameDataPointer);
		jsonArray.push_back(gameDataStringPointer->raw_string);
		return;
	}

	// number / scalar
	if (element.type() == game_data_number::type_def)
	{
		intercept::sqf::system_chat("RV scalar");
		auto gameDataNumberPointer = static_cast<game_data_number*>(GameDataPointer);
		jsonArray.push_back(gameDataNumberPointer->number);
		return;
	}

	// bool
	if (element.type() == game_data_bool::type_def)
	{
		intercept::sqf::system_chat("RV bool");
		auto gameDataBoolPointer = static_cast<game_data_bool*>(GameDataPointer);
		jsonArray.push_back(gameDataBoolPointer->val);
		return;
	}
}

nlohmann::json process_array(game_value& element)
{
	nlohmann::json jsonArray = nlohmann::json::array();

	if (canJson(element) && element.type() != game_data_array::type_def)
	{
		push_back_internal(element, jsonArray);
	}
	

	// RV array
	if (element.type() == game_data_array::type_def)
	{

		//convert to array.
		auto& array = element.to_array();

		for (size_t i = 0; i < element.size(); i++)
		{
			auto& arrayElement = array[i];
			if (arrayElement.type() == game_data_array::type_def)
			{
				jsonArray.push_back(process_array(arrayElement));
			}
			else
			{
				push_back_internal(arrayElement, jsonArray);
			}
			//intercept::sqf::system_chat(intercept::sqf::str(arrayElement));
		}

	}

	if (!canJson(element))
	{
		jsonArray.push_back(intercept::sqf::str(element));
	}


	return jsonArray;
}


/*
* @brief pushBack function
* @author Killerswin2
* @param jsonArray 
* @param rightArg
* @return nothing
*/
game_value push_back_json_array(game_value_parameter jsonArray, game_value_parameter rightArg)
{
	if (jsonArray.is_nil())
	{
		return {};
	}
	auto jsonPointer = static_cast<game_data_json_array*>(jsonArray.data.get());

	// we need to check the type of data to due specific stuff

	if (canJson(rightArg) && rightArg.type() != game_data_array::type_def)
	{
		push_back_internal(rightArg, jsonPointer->jsonArray);
	}

	if (!canJson(rightArg))
	{
		jsonPointer->jsonArray.push_back(intercept::sqf::str(rightArg));
	}

	// array
	if (rightArg.type() == game_data_array::type_def)
	{
		// this is going to be slow. like very slow
		intercept::sqf::system_chat("RV array");
		nlohmann::json jsonArray = nlohmann::json::array();

		//convert to array.
		auto& array = rightArg.to_array();


		for (size_t i = 0; i < rightArg.size(); i++)
		{
			auto& arrayElement = array[i];
			if (arrayElement.type() == game_data_array::type_def)
			{
				jsonArray.push_back(process_array(arrayElement));
			} 
			else
			{
				push_back_internal(arrayElement, jsonArray);
			}
			intercept::sqf::system_chat(intercept::sqf::str(arrayElement));
		}
		jsonPointer->jsonArray.push_back(jsonArray);

	}


	return {};
}


/*
   * @brief prints out json data
   * @detail this is done async it logs the data to a file, documents for windows, var/log for linux
   * @author Killerswin2
   * @return BOOL returns true always
   */
void fileOperationsInternal(game_value_parameter jsonArray)
{

	//@todo discuss a default log path, as users might not have a c: or d: drive also, its windows specific right now
	std::filesystem::path fsfilepath;
	std::ofstream MyFile;
	auto jsonObjectPointer = static_cast<game_data_json_array*>(jsonArray.data.get());

	//@todo linux here
	//filepath here /var/log/yourapp.log

	// change the log file location
#ifdef _WIN32
//FOLDERID_Documents
	wchar_t* path;
	HRESULT handleResult = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &path);
	if (SUCCEEDED(handleResult))
	{
		std::wstring new_path = path;
		new_path.append(L"\\anti\\json\\test.json");
		fsfilepath = new_path;
	}
#endif

	// @Todo better file error handling here
	MyFile.open(fsfilepath, std::ios_base::app);
	if (MyFile.bad())
	{
		std::cout << "my is null" << std::endl;
	}
	MyFile << jsonObjectPointer->jsonArray.dump(-2) << "\n";
	MyFile.close();

#ifdef _WIN32
	CoTaskMemFree(path);
#endif
}

game_value jsonDump(game_value_parameter jsonArray)
{
	auto jsonObjectPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	auto ret = std::async(std::launch::async, fileOperationsInternal, jsonArray);
	return {};
}


game_value is_empty_json_array(game_value_parameter jsonArray)
{
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	return jsonArrayPointer->jsonArray.empty();

}

//returns the count of elements with key
game_value count_json_array_key(game_value_parameter jsonArray, game_value_parameter key)
{
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	return jsonArrayPointer->jsonArray.count(key);
}


// returns number of elements
game_value count_json_array(game_value_parameter jsonArray)
{
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	return jsonArrayPointer->jsonArray.size();
}

game_value last_element_json_array(game_value_parameter jsonArray)
{
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	if (jsonArrayPointer->jsonArray.empty())
	{
		return -1;
	}
	else
	{
		auto back = jsonArrayPointer->jsonArray.back();
		if (back.is_string())
		{
			return game_value(new game_data_string(back));
		}

		if (back.is_boolean())
		{
			return game_value(new game_data_bool(back));
		}

		if (back.is_number())
		{
			return game_value(new game_data_number(back));
		}

		if (back.is_array())
		{
			return game_value(new game_data_json_array(back));
		}

		if (back.is_object())
		{
			return game_value(new game_data_json(back));
		}

	}
	// should not reach here
	return "reached end here";
}

game_value clear_json_array(game_value_parameter jsonArray)
{
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	jsonArrayPointer->jsonArray.clear();
	return {};
}

void json_game_data::jsonArray::pre_start()
{
	auto codeType = intercept::client::host::register_sqf_type("JSONARRAY"sv, "jsonArray"sv, "json array stuff", "jsonArray"sv, create_game_data_json_array);
	game_data_json_array_type = codeType.second;

	Commands& commands = Commands::get();
	commands.addCommand("createJsonArray", "create a json array", userFunctionWrapper<create_json_array>, codeType.first);
	commands.addCommand("pushBack","push back element to json array", userFunctionWrapper<push_back_json_array>, game_data_type::NOTHING, codeType.first, game_data_type::ANY);
	commands.addCommand("dumpToFile", "dumps object to file", userFunctionWrapper<jsonDump>, game_data_type::NOTHING, codeType.first);
	commands.addCommand("empty", "checks if a json array is empty", userFunctionWrapper<is_empty_json_array>, game_data_type::BOOL, codeType.first);
	commands.addCommand("count", "returns number keys", userFunctionWrapper<count_json_array>, game_data_type::SCALAR, codeType.first);
	commands.addCommand("count", "returns number elements with key", userFunctionWrapper<count_json_array_key>, game_data_type::SCALAR, codeType.first, game_data_type::STRING);
	commands.addCommand("back", "returns the last element in the json array", userFunctionWrapper<last_element_json_array>, game_data_type::ANY, codeType.first);
	commands.addCommand("clear", "clears the contents of the json array", userFunctionWrapper<clear_json_array>, game_data_type::NOTHING, codeType.first);
}