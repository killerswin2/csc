#include "json.hpp"
#include "../commands.hpp"
#include <ostream>
#include <istream>
#include <fstream>
#include <future>
#include <vector>
#include <stack>

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

/*
 * @brief internal function for json object creation
 * @detail everything besides rvArrays
 * @param key - key for json object
 * @param element - game_value element that was passed in.
 * @param jsonObject - json object to work on
 * @author Killerswin2
 * @return game_value
*/
void json_object_creation_internal(const char * key, const game_value& element, nlohmann::json& jsonObject)
{
	game_data* GameDataPointer = element.data.get();
	if (!canJson(element))
	{
		//@TODO we need to tell the user that they passed in an wrong type for json.
	}

	//json data type
	if (GameDataPointer->type() == game_data_json_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json*>(GameDataPointer);
		jsonObject[key] = (jsonObjectPointer->jsonObject);
		return;
	}
	// json array
	if (GameDataPointer->type() == game_data_json_array_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json_array*>(GameDataPointer);
		jsonObject[key] = jsonObjectPointer->jsonArray;
		return;
	}

	// string
	if (element.type() == game_data_string::type_def)
	{
		auto gameDataStringPointer = static_cast<game_data_string*>(GameDataPointer);
		jsonObject[key] = (gameDataStringPointer->raw_string);
		return;
	}

	// number / scalar
	if (element.type() == game_data_number::type_def)
	{
		auto gameDataNumberPointer = static_cast<game_data_number*>(GameDataPointer);
		jsonObject[key] = (gameDataNumberPointer->number);
		return;
	}

	// bool
	if (element.type() == game_data_bool::type_def)
	{
		auto gameDataBoolPointer = static_cast<game_data_bool*>(GameDataPointer);
		jsonObject[key] = (gameDataBoolPointer->val);
		return;
	}
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
		//@TODO gs here, that the element was not an accepted type for json
		return;
	}
		

	//json data type
	if (GameDataPointer->type() == game_data_json_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json*>(GameDataPointer);
		jsonArray.push_back(jsonObjectPointer->jsonObject);
		return;
	}
	// json array
	if (GameDataPointer->type() == game_data_json_array_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json_array*>(GameDataPointer);
		jsonArray.push_back(jsonObjectPointer->jsonArray);
		return;
	}

	// string
	if (element.type() == game_data_string::type_def)
	{
		auto gameDataStringPointer = static_cast<game_data_string*>(GameDataPointer);
		jsonArray.push_back(gameDataStringPointer->raw_string);
		return;
	}

	// number / scalar
	if (element.type() == game_data_number::type_def)
	{
		auto gameDataNumberPointer = static_cast<game_data_number*>(GameDataPointer);
		jsonArray.push_back(gameDataNumberPointer->number);
		return;
	}

	// bool
	if (element.type() == game_data_bool::type_def)
	{
		auto gameDataBoolPointer = static_cast<game_data_bool*>(GameDataPointer);
		jsonArray.push_back(gameDataBoolPointer->val);
		return;
	}
}


void process_array(const game_value& element, nlohmann::json& jsonArray)
{
	
	std::stack<game_value> gameValueStack;
	std::stack<nlohmann::json> jsonArrayPushBackers;

	size_t index = 0;

	//convert to array.
	auto& array = element.to_array();

	while (!gameValueStack.empty() || index < array.size())
	{
		auto& arrayElement = array[index];
		if (arrayElement.type() == game_data_array::type_def)
		{
			// push to stack if array, game_value and jsonArrayObject
			gameValueStack.push(arrayElement);
			jsonArrayPushBackers.push(jsonArray);
			jsonArray = nlohmann::json::array();
			array = arrayElement.to_array();
			index = 0;
			continue;
		}
		else
		{
			push_back_internal(arrayElement, jsonArray);
		}

		if (index == array.size() - 1 && !gameValueStack.empty())
		{
			nlohmann::json* temp = &jsonArray;
			array = gameValueStack.top().to_array();
			jsonArray = jsonArrayPushBackers.top();
			gameValueStack.pop();
			jsonArrayPushBackers.pop();
			jsonArray.push_back(*temp);
			index = jsonArray.size();
		}
		index++;
	}
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

	if (rightArg.type() != game_data_array::type_def)
	{
		push_back_internal(rightArg, jsonPointer->jsonArray);
	}

	// array
	if (rightArg.type() == game_data_array::type_def)
	{
		nlohmann::json jsonArray = nlohmann::json::array();
		process_array(rightArg, jsonArray);
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
	if (jsonArray.is_nil())
	{
		return {};
	}
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	return jsonArrayPointer->jsonArray.empty();

}


/*
 * @brief  returns the count of elements with key
 * @detail this is might not be working right for array objects
 * @param jsonArray - json array to count
 * @param key - string key to search/count for
 * @author Killerswin2
 * @return float of size of array
*/
game_value count_json_array_key(game_value_parameter jsonArray, game_value_parameter key)
{
	if (jsonArray.is_nil())
	{
		return {};
	}
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	return jsonArrayPointer->jsonArray.count(key);
}


/*
* @brief  returns number of elements
* @detail 
* @param jsonArray - json array to count
* @author Killerswin2
* @return float of size of array
*/
game_value count_json_array(game_value_parameter jsonArray)
{
	if (jsonArray.is_nil())
	{
		return {};
	}
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	return jsonArrayPointer->jsonArray.size();
}

/*
 * @brief  returns the last element in the json array
 * @detail returns the last element in the json array. Depending on the type of "object" in the element it can return 
 * a string, bool, number, json array, or json object
 * @param jsonArray - json array to work on
 * @author Killerswin2
 * @return game_value
*/
game_value last_element_json_array(game_value_parameter jsonArray)
{
	if (jsonArray.is_nil())
	{
		return {};
	}
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

/*
 * @brief  clears the json array to it's default state
 * @detail clearing the json array sets the array to []
 * @param jsonArray - json array to work on
 * @author Killerswin2
 * @return game_value - nothing
*/
game_value clear_json_array(game_value_parameter jsonArray)
{
	if (jsonArray.is_nil())
	{
		return {};
	}
	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	jsonArrayPointer->jsonArray.clear();
	return {};
}

/*
 * @brief  json array to rv array convertor
 * @detail converts each element to the right rv type. Strings, scalars, bool, and nested arrays
 * @param jsonArray - json array to work on
 * @param list - intercept auto_array
 * @author Killerswin2
*/
void json_array_convertor(nlohmann::json& element, intercept::types::auto_array<game_value>& list)
{
	if (element.is_string())
	{
		list.push_back(game_value(new game_data_string(element)));
	}

	if (element.is_boolean())
	{
		list.push_back(game_value(new game_data_bool(element)));
	}

	if (element.is_number())
	{
		list.push_back(game_value(new game_data_number(element)));
	}

	if (element.is_array())
	{
		intercept::types::auto_array<game_value> nestList;
		nlohmann::json::iterator iter = element.begin();
		nlohmann::json::const_iterator endIt = element.end();

		while (iter != endIt)
		{
			json_array_convertor(*iter, nestList);
			iter++;
		}
		list.push_back(nestList);
	}

	//@TODO handled is_object case
	if (element.is_object())
	{
		list.push_back(game_value(new game_data_json(element)));
	}
}

/*
 * @brief handles top level array but not nested arrays.
 * @detail nested arrays are handled by <json_array_convertor>
 * @param jsonArray - json array to work on
 * @author Killerswin2
 * @return game_value
*/
game_value convert_json_array_to_array(game_value_parameter jsonArray)
{
	
	if (jsonArray.is_nil())
	{
		return {};
	}

	// create game_value array
	intercept::types::auto_array<game_value> list;

	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());

	nlohmann::json::iterator iter = jsonArrayPointer->jsonArray.begin();
	nlohmann::json::const_iterator endIt = jsonArrayPointer->jsonArray.end();

	// go through the array, and convert the elements

	while (iter != endIt)
	{
		json_array_convertor(*iter, list);
		iter++;
	}

	return game_value(list);
}

/*
 * @brief inserts element into json object
 * @detail 
 * @param jsonArray - json array to work on
 * @author Killerswin2
 * @return game_value
*/
game_value insert_json_array(game_value_parameter jsonArray, game_value_parameter rvArray)
{
	// not nil and array has at least two elements
	if (jsonArray.is_nil() && rvArray.size() > 1)
	{
		return {};
	}

	auto jsonArrayPointer = static_cast<game_data_json_array*>(jsonArray.data.get());

	// this function has specific options in the rvArray, we need to check these.
	size_t arraySize = rvArray.size();

	// object location in array that has the data
	size_t valueIndex = arraySize -1;

	if (!canJson(rvArray[valueIndex])) {
		return {};
	}

	auto gameDataPointer = rvArray[valueIndex].data.get();

	//check if the last item is a jsonArray or something else
	if (gameDataPointer->type() == game_data_json_array_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json_array*>(gameDataPointer);
		auto gameDataNumberPointer = static_cast<game_data_number*>(rvArray[0].data.get());
		int index = static_cast<int>(gameDataNumberPointer->number);
		nlohmann::json::iterator iter;

		switch (valueIndex)
		{
			case 1: {iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, jsonObjectPointer->jsonArray); break; }
			case 2: {
				int count = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);
				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, count, jsonObjectPointer->jsonArray);
				break;
			}
			case 3: {
				int sliceStart = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 2].data.get())->number);
				int sliceEnd = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);

				//@TODO notify user of index out of bounds
				if (sliceStart > jsonObjectPointer->jsonArray.size() || sliceEnd > jsonObjectPointer->jsonArray.size())
				{
					return -2;
				}

				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, jsonObjectPointer->jsonArray.begin() + sliceStart, jsonObjectPointer->jsonArray.begin() + sliceEnd);
				break;
			}
		}

		return game_value(static_cast<int>(iter - jsonArrayPointer->jsonArray.begin()));
	}

	// json objects
	if (gameDataPointer->type() == game_data_json_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json*>(gameDataPointer);
		auto gameDataNumberPointer = static_cast<game_data_number*>(rvArray[0].data.get());
		int index = static_cast<int>(gameDataNumberPointer->number);
		nlohmann::json::iterator iter;

		switch (valueIndex)
		{
			case 1: {iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, jsonObjectPointer->jsonObject); break; }
			case 2: {
				int count = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);
				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, count, jsonObjectPointer->jsonObject);
				break;
			}
			case 3: {
				int sliceStart = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 2].data.get())->number);
				int sliceEnd = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);

				//@TODO notify user of index out of bounds
				if (sliceStart > jsonObjectPointer->jsonObject.size() || sliceEnd > jsonObjectPointer->jsonObject.size())
				{
					return -2;
				}

				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, jsonObjectPointer->jsonObject.begin() + sliceStart, jsonObjectPointer->jsonObject.begin() + sliceEnd);
				break;
			}
		}

		return game_value(static_cast<int>(iter - jsonArrayPointer->jsonArray.begin()));
	}

	if (rvArray[valueIndex].type() == game_data_array::type_def)
	{
		nlohmann::json convertedArray;

		auto& array = rvArray[valueIndex].to_array();
		process_array(rvArray[valueIndex], convertedArray);

		// grab the number from index zero, cast to int, then insert createdArray
		auto gameDataNumberPointer = static_cast<game_data_number*>(rvArray[0].data.get());
		int index = static_cast<int>(gameDataNumberPointer->number);
		nlohmann::json::iterator iter;

		switch (valueIndex)
		{
			case 1: {iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, convertedArray); break; }
			case 2: {
				int count = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);
				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, count, convertedArray);
				break;
			}
			case 3: {
				int sliceStart = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 2].data.get())->number);
				int sliceEnd = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);

				//@TODO notify user of index out of bounds
				if (sliceStart > convertedArray.size() || sliceEnd > convertedArray.size())
				{
					return -2;
				}

				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, convertedArray.begin() + sliceStart, convertedArray.begin() + sliceEnd);
				break;
			}
		}

		return game_value(static_cast<int>(iter - jsonArrayPointer->jsonArray.begin()));

	}

	// string types
	if (rvArray[valueIndex].type() == game_data_string::type_def)
	{
		auto gameDataNumberPointer = static_cast<game_data_number*>(rvArray[0].data.get());
		auto gameDataStringPointer = static_cast<game_data_string*>(gameDataPointer);
		int index = static_cast<int>(gameDataNumberPointer->number);
		nlohmann::json::iterator iter;

		switch (valueIndex)
		{
			case 1: {iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, gameDataStringPointer->raw_string); break; }
			case 2: {
				int count = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);
				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, count, gameDataStringPointer->raw_string);
				break;
			}
		}

		return game_value(static_cast<int>(iter - jsonArrayPointer->jsonArray.begin()));
	}

	// number types
	if (rvArray[valueIndex].type() == game_data_number::type_def)
	{
		auto gameDataNumberPointer = static_cast<game_data_number*>(rvArray[0].data.get());
		auto gameDataNumberPointer2 = static_cast<game_data_number*>(gameDataPointer);
		int index = static_cast<int>(gameDataNumberPointer->number);
		nlohmann::json::iterator iter;

		switch (valueIndex)
		{
			case 1: {iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, gameDataNumberPointer2->number); break; }
			case 2: {
				int count = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);
				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, count, gameDataNumberPointer2->number);
				break;
			}
		}

		return game_value(static_cast<int>(iter - jsonArrayPointer->jsonArray.begin()));
	}

	// bool types
	if (rvArray[valueIndex].type() == game_data_bool::type_def)
	{
		auto gameDataNumberPointer = static_cast<game_data_number*>(rvArray[0].data.get());
		auto gameDataBoolPointer = static_cast<game_data_bool*>(gameDataPointer);
		int index = static_cast<int>(gameDataNumberPointer->number);
		nlohmann::json::iterator iter;
		switch (valueIndex)
		{
			case 1: {iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, gameDataBoolPointer->val); break;}
			case 2: {
				int count = static_cast<int>(static_cast<game_data_number*>(rvArray[valueIndex - 1].data.get())->number);
				iter = jsonArrayPointer->jsonArray.insert(jsonArrayPointer->jsonArray.begin() + index, count, gameDataBoolPointer->val);
				break; 
			}
		}
		
		return game_value(static_cast<int>(iter - jsonArrayPointer->jsonArray.begin()));
	}

	// generic error
	return -1;
}

/*
 * @brief erase from json array a slice of elements
 * @detail
 * @param jsonArray - json array to work on
 * @param rvArray - json slice indices [start, end]
 * @author Killerswin2
 * @return game_value
*/
game_value erase_json_array(game_value_parameter jsonArray, game_value_parameter rvArray)
{
	// not nil and array has at least two elements
	if (jsonArray.is_nil() && rvArray.size() > 1)
	{
		return {};
	}
	auto gameDataJsonPointer = static_cast<game_data_json_array*>(jsonArray.data.get());
	int startSlice = rvArray[0];
	int endSlice = rvArray[1];

	auto iter = gameDataJsonPointer->jsonArray.erase(gameDataJsonPointer->jsonArray.begin() + startSlice, gameDataJsonPointer->jsonArray.begin() + endSlice);

	return static_cast<int>(iter - gameDataJsonPointer->jsonArray.begin());
}

/*
 * @brief erase from json array by index
 * @detail
 * @param jsonArray - json array to work on
 * @param index - index to erase from json array
 * @author Killerswin2
 * @return game_value
*/
game_value erase_json_array_index(game_value_parameter jsonArray, game_value_parameter index)
{
	// not nil and array has at least two elements
	if (jsonArray.is_nil())
	{
		return {};
	}
	auto gameDataJsonPointer = static_cast<game_data_json_array*>(jsonArray.data.get());

	gameDataJsonPointer->jsonArray.erase(index);

	return {};
}


/*
 * @brief internal function for emplacing back data to the jsonArray
 * @detail
 * @param element - game_value element that was passed in.
 * @param jsonArray - json array to work on
 * @author Killerswin2
 * @return game_value
*/
void emplace_back_internal(const game_value& element, nlohmann::json& jsonArray)
{
	game_data* GameDataPointer = element.data.get();
	if (!canJson(element))
	{
		//@TODO we need to tell the user that they passed in an wrong type for json.
		return;
	}

	//json data type
	if (GameDataPointer->type() == game_data_json_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json*>(GameDataPointer);
		jsonArray.emplace_back(jsonObjectPointer->jsonObject);
		return;
	}
	// json array
	if (GameDataPointer->type() == game_data_json_array_type)
	{
		auto jsonObjectPointer = static_cast<game_data_json_array*>(GameDataPointer);
		jsonArray.emplace_back(jsonObjectPointer->jsonArray);
		return;
	}

	// string
	if (element.type() == game_data_string::type_def)
	{
		auto gameDataStringPointer = static_cast<game_data_string*>(GameDataPointer);
		jsonArray.emplace_back(gameDataStringPointer->raw_string);
		return;
	}

	// number / scalar
	if (element.type() == game_data_number::type_def)
	{
		auto gameDataNumberPointer = static_cast<game_data_number*>(GameDataPointer);
		jsonArray.emplace_back(gameDataNumberPointer->number);
		return;
	}

	// bool
	if (element.type() == game_data_bool::type_def)
	{
		auto gameDataBoolPointer = static_cast<game_data_bool*>(GameDataPointer);
		jsonArray.emplace_back(gameDataBoolPointer->val);
		return;
	}
}



/*
 * @brief emplaces to the back of the json array, a json value from the args
 * @detail
 * @param jsonArray - json array to emplace back
 * @param rightArgs - args to construct and emplace back
 * @author Killerswin2
 * @return game_value
*/
game_value emplace_back_json_array(game_value_parameter jsonArray, game_value_parameter rightArgs)
{
	if (jsonArray.is_nil())
	{
		return {};
	}

	// json game_data type
	game_data_json_array* jsonPointer = static_cast<game_data_json_array*>(jsonArray.data.get());

	if (rightArgs.size() == 2)
	{
		// okay the size is two, therefore [key, value] -> create a json object here then.

		// json key
		const char* key;


		if (rightArgs[0].type() != game_data_string::type_def)
		{
			// @TODO gs tell the user that the first element in the array must be a string
			return {};
		}
		else
		{
			key = static_cast<game_data_string*>(rightArgs[0].data.get())->raw_string.c_str();
		}

		if (rightArgs[1].type() == game_data_array::type_def)
		{
			nlohmann::json nestedArray = nlohmann::json::array();
			process_array(rightArgs[1], nestedArray);
			nlohmann::json jsonObject;
			jsonObject[key] = nestedArray;
			jsonPointer->jsonArray.emplace_back(jsonObject);
		}

		// check that there isn't an array in index 1, else you will get null returns
		if (canJson(rightArgs[1]) && rightArgs[1].type() != game_data_array::type_def)
		{
			nlohmann::json jsonObject;
			json_object_creation_internal(key, rightArgs[1], jsonObject);
			jsonPointer->jsonArray.emplace_back(jsonObject);
		}

	}

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
	commands.addCommand("toArray", "returns an RV array from a json array", userFunctionWrapper<convert_json_array_to_array>, game_data_type::ARRAY, codeType.first);
	commands.addCommand("insert", "inserts element in to the json array", userFunctionWrapper<insert_json_array>, game_data_type::SCALAR, codeType.first, game_data_type::ARRAY);
	commands.addCommand("erase", "removes element from JSON element range", userFunctionWrapper<erase_json_array>, game_data_type::SCALAR, codeType.first, game_data_type::ARRAY);
	commands.addCommand("erase", "removes an element from a JSON array by index", userFunctionWrapper<erase_json_array_index>, game_data_type::NOTHING, codeType.first, game_data_type::SCALAR);
	commands.addCommand("emplaceBack", "Creates a JSON value from supplied args", userFunctionWrapper<emplace_back_json_array>, game_data_type::NOTHING, codeType.first, game_data_type::ARRAY);

}