#ifndef JSON_H
#define JSON_H

#include <intercept.hpp>
#include <string_view>
#include <nlohmann/json.hpp>

namespace json_game_data
{
	class json
	{
	public:
		static void pre_start();
	};

	class jsonArray
	{
	public:
		static void pre_start();
	};
}


class game_data_json : public game_data {

public:
	game_data_json() {}
	game_data_json(nlohmann::json object) : jsonObject{ object } {}
	void lastRefDeleted() const override { delete this; }
	const sqf_script_type& type() const override;
	~game_data_json() override {};

	bool get_as_bool() const override { return true; };
	float get_as_number() const override { return 0.f; }
	const r_string& get_as_string() const override { static r_string nm("json"sv); return nm; }
	game_data* copy() const override { return new game_data_json(*this); }
	r_string to_string() const override { return r_string("json"sv); }
	const char* type_as_string() const override { return "json"; }
	bool is_nil() const override { return false; }
	bool can_serialize() override { return true; }
	serialization_return serialize(param_archive& ar) override;
	nlohmann::json jsonObject;
};

class game_data_json_array : public game_data {

public:
	game_data_json_array() {}
	game_data_json_array(nlohmann::json object) {
		jsonArray = object;
	}
	void lastRefDeleted() const override { delete this; }
	const sqf_script_type& type() const override;
	~game_data_json_array() override {};

	bool get_as_bool() const override { return true; };
	float get_as_number() const override { return 0.f; }
	const r_string& get_as_string() const override { static r_string nm("jsonArray"sv); return nm; }
	game_data* copy() const override { return new game_data_json_array(*this); }
	r_string to_string() const override { return r_string("jsonArray"sv); }
	const char* type_as_string() const override { return "jsonArray"; }
	bool is_nil() const override { return false; }
	bool can_serialize() override { return true; }
	serialization_return serialize(param_archive& ar) override;
	nlohmann::json jsonArray;
};

// other functions

bool canJson(const game_value& element);

#endif // !JSON_H