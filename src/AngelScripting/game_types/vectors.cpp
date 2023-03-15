#include "vectors.hpp"

void vector2_constructor(vector2* memory)
{
    new(memory) vector2();
}

void vector2_constructor(float x, float y, vector2* memory)
{
    new(memory) vector2(x, y);
}

void vector2_destructor(vector2* memory)
{
    memory->~vector2();
}

void vector3_constructor(vector3* memory)
{
    new(memory) vector3();
}

void vector3_constructor(float x, float y, float z, vector3* memory)
{
    new(memory) vector3(x, y, z);
}

void vector3_destructor(vector3* memory)
{
    memory->~vector3();
}

void register_vectors_generic(asIScriptEngine*& engine)
{
    std::cout << "Not Implemented right now!";
}


void register_vectors_native(asIScriptEngine*& engine)
{
    int retCode;
    retCode = engine->SetDefaultNamespace(""); assert(retCode >= 0);

    retCode = engine->RegisterObjectType("vector3", sizeof(vector3), asOBJ_VALUE | asGetTypeTraits<vector3>() | asOBJ_POD); assert(retCode >= 0);
    retCode = engine->RegisterObjectType("vector2", sizeof(vector2), asOBJ_VALUE | asGetTypeTraits<vector2>() | asOBJ_POD); assert(retCode >= 0);

    //vec2
    retCode = engine->RegisterObjectProperty("vector2", "float x", asOFFSET(vector2, x)); assert(retCode >= 0);
    retCode = engine->RegisterObjectProperty("vector2", "float y", asOFFSET(vector2, y)); assert(retCode >= 0);

    retCode = engine->RegisterObjectBehaviour("vector2", asBEHAVE_CONSTRUCT, "void f( float x, float y)", asFUNCTIONPR(vector2_constructor, (float, float, vector2*), void), asCALL_CDECL_OBJLAST); assert(retCode >= 0);
    retCode = engine->RegisterObjectBehaviour("vector2", asBEHAVE_CONSTRUCT, "void f()", asFUNCTIONPR(vector2_constructor, (vector2*), void), asCALL_CDECL_OBJLAST); assert(retCode >= 0);
    retCode = engine->RegisterObjectBehaviour("vector2", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(vector2_destructor), asCALL_CDECL_OBJLAST); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opAssign( vector2 &in)", asMETHOD(vector2, operator=), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 opMul( float &in)", asMETHODPR(vector2, operator*, (const float&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 opDiv( float &in)", asMETHODPR(vector2, operator/, (const float&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 opAdd( vector2 &in)", asMETHODPR(vector2, operator+, (const vector2&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 opAdd( vector3 &in)", asMETHODPR(vector2, operator+, (const vector3&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 opDiv( vector2 &in)", asMETHODPR(vector2, operator/, (const vector2&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 opDiv( vector3 &in)", asMETHODPR(vector2, operator/, (const vector3&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 opMul( vector2 &in)", asMETHODPR(vector2, operator*, (const vector2&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 opMul( vector3 &in)", asMETHODPR(vector2, operator*, (const vector3&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 opSub( vector2 &in)", asMETHODPR(vector2, operator-, (const vector2&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 opSub( vector3 &in)", asMETHODPR(vector2, operator-, (const vector3&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 opSub()", asMETHODPR(vector2, operator-, () const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opMulAssign( vector2 &in)", asMETHODPR(vector2, operator*=, (const vector2&), vector2&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opMulAssign( vector3 &in)", asMETHODPR(vector2, operator*=, (const vector3&), vector2&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opMulAssign(float other)", asMETHODPR(vector2, operator*=, (const float), vector2&), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opDivAssign( vector2 &in)", asMETHODPR(vector2, operator/=, (const vector2&), vector2&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opDivAssign( vector3 &in)", asMETHODPR(vector2, operator/=, (const vector3&), vector2&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opDivAssign( float other)", asMETHODPR(vector2, operator/=, (const float), vector2&), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opAddAssign( vector2 &in)", asMETHODPR(vector2, operator+=, (const vector2&), vector2&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opAddAssign( vector3 &in)", asMETHODPR(vector2, operator+=, (const vector3&), vector2&), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opSubAssign( vector2 &in)", asMETHODPR(vector2, operator-=, (const vector2&), vector2&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 &opSubAssign( vector3 &in)", asMETHODPR(vector2, operator-=, (const vector3&), vector2&), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float magnitude()", asMETHOD(vector2, magnitude), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float magnitude_squared()", asMETHOD(vector2, magnitude_squared), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float dot( vector2 &in)", asMETHODPR(vector2, dot, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float dot( vector3 &in)", asMETHODPR(vector2, dot, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float cos( vector2 &in)", asMETHODPR(vector2, cos, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float cos( vector3 &in)", asMETHODPR(vector2, cos, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float angle( vector2 &in)", asMETHODPR(vector2, angle, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float angle( vector3 &in)", asMETHODPR(vector2, angle, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float get_azimuth( vector2 &in)", asMETHODPR(vector2, get_azimuth, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float get_azimuth( vector3 &in)", asMETHODPR(vector2, get_azimuth, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float& get_dir( vector2 &in)", asMETHODPR(vector2, get_dir, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float& get_dir( vector3 &in)", asMETHODPR(vector2, get_dir, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float distance( vector2 &in)", asMETHODPR(vector2, distance, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float distance( vector3 &in)", asMETHODPR(vector2, distance, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "float distance_squared( vector2 &in)", asMETHODPR(vector2, distance_squared, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "float distance_squared( vector3 &in)", asMETHODPR(vector2, distance_squared, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 normalize()", asMETHOD(vector2, normalize), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 rotate(float rad)", asMETHOD(vector2, rotate), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 rotate_deg(float deg)", asMETHOD(vector2, rotate_deg), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "bool zero_distance()", asMETHOD(vector2, zero_distance), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 dir_to( vector2 &in)", asMETHODPR(vector2, dir_to, (const vector2&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 dir_to( vector3 &in)", asMETHODPR(vector2, dir_to, (const vector3&) const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector2", "vector2 lerp( vector2 &in, float percent)", asMETHODPR(vector2, lerp, (const vector2&, const float) const, vector2), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector2", "vector2 slerp( vector2 &in, float percent)", asMETHODPR(vector2, slerp, (const vector2&, const float) const, vector2), asCALL_THISCALL); assert(retCode >= 0);

    //vec3
    retCode = engine->RegisterObjectProperty("vector3", "float x", asOFFSET(vector3, x)); assert(retCode >= 0);
    retCode = engine->RegisterObjectProperty("vector3", "float y", asOFFSET(vector3, y)); assert(retCode >= 0);
    retCode = engine->RegisterObjectProperty("vector3", "float z", asOFFSET(vector3, z)); assert(retCode >= 0);

    retCode = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT, "void f(float x, float y, float z)", asFUNCTIONPR(vector3_constructor, (float, float, float, vector3*), void), asCALL_CDECL_OBJLAST); assert(retCode >= 0);
    retCode = engine->RegisterObjectBehaviour("vector3", asBEHAVE_CONSTRUCT, "void f()", asFUNCTIONPR(vector3_constructor, (vector3*), void), asCALL_CDECL_OBJLAST); assert(retCode >= 0);
    retCode = engine->RegisterObjectBehaviour("vector3", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(vector3_destructor), asCALL_CDECL_OBJLAST); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 opAssign(vector3 other)", asMETHOD(vector3, operator=), asCALL_THISCALL);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 opMul( float &in)", asMETHODPR(vector3, operator*, (const float&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 opDiv( float &in)", asMETHODPR(vector3, operator/, (const float&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 opAdd( vector2 &in)", asMETHODPR(vector3, operator+, (const vector2&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 opAdd( vector3 &in)", asMETHODPR(vector3, operator+, (const vector3&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    //retCode = engine->RegisterObjectMethod("vector3", "vector3 opDiv( vector2 &in)", asMETHODPR(vector3, operator/, (const vector2&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 opDiv( vector3 &in)", asMETHODPR(vector3, operator/, (const vector3&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 opMul( vector2 &in)", asMETHODPR(vector3, operator*, (const vector2&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 opMul( vector3 &in)", asMETHODPR(vector3, operator*, (const vector3&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 opSub( vector2 &in)", asMETHODPR(vector3, operator-, (const vector2&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 opSub( vector3 &in)", asMETHODPR(vector3, operator-, (const vector3&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 opSub()", asMETHODPR(vector3, operator-, () const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opMulAssign( vector2 &in)", asMETHODPR(vector3, operator*=, (const vector2&), vector3&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opMulAssign( vector3 &in)", asMETHODPR(vector3, operator*=, (const vector3&), vector3&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opMulAssign(float other)", asMETHODPR(vector3, operator*=, (const float), vector3&), asCALL_THISCALL); assert(retCode >= 0);

    //retCode = engine->RegisterObjectMethod("vector3", "vector3 &opDivAssign( vector2 &in)", asMETHODPR(vector3, operator/=, (const vector2&), vector3&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opDivAssign( vector3 &in)", asMETHODPR(vector3, operator/=, (const vector3&), vector3&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opDivAssign( float other)", asMETHODPR(vector3, operator/=, (const float), vector3&), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opAddAssign( vector2 &in)", asMETHODPR(vector3, operator+=, (const vector2&), vector3&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opAddAssign( vector3 &in)", asMETHODPR(vector3, operator+=, (const vector3&), vector3&), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opSubAssign( vector2 &in)", asMETHODPR(vector3, operator-=, (const vector2&), vector3&), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 &opSubAssign( vector3 &in)", asMETHODPR(vector3, operator-=, (const vector3&), vector3&), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float magnitude()", asMETHOD(vector3, magnitude), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float magnitude_squared()", asMETHOD(vector3, magnitude_squared), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float dot( vector2 &in)", asMETHODPR(vector3, dot, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float dot( vector3 &in)", asMETHODPR(vector3, dot, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float cos( vector2 &in)", asMETHODPR(vector3, cos, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float cos( vector3 &in)", asMETHODPR(vector3, cos, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float angle( vector2 &in)", asMETHODPR(vector3, angle, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float angle( vector3 &in)", asMETHODPR(vector3, angle, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float get_azimuth( vector2 &in)", asMETHODPR(vector3, get_azimuth, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float get_azimuth( vector3 &in)", asMETHODPR(vector3, get_azimuth, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float& get_dir( vector2 &in)", asMETHODPR(vector3, get_dir, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float& get_dir( vector3 &in)", asMETHODPR(vector3, get_dir, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float distance( vector2 &in)", asMETHODPR(vector3, distance, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float distance( vector3 &in)", asMETHODPR(vector3, distance, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float distance_squared( vector2 &in)", asMETHODPR(vector3, distance_squared, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float distance_squared( vector3 &in)", asMETHODPR(vector3, distance_squared, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float distance_2d( vector2 &in)", asMETHODPR(vector3, distance_2d, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float distance_2d( vector3 &in)", asMETHODPR(vector3, distance_2d, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "float distance_2d_squared( vector2 &in)", asMETHODPR(vector3, distance_2d_squared, (const vector2&) const, float), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "float distance_2d_squared( vector3 &in)", asMETHODPR(vector3, distance_2d_squared, (const vector3&) const, float), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 cross( vector2 &in)", asMETHODPR(vector3, cross, (const vector2&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 cross( vector3 &in)", asMETHODPR(vector3, cross, (const vector3&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 normalize()", asMETHOD(vector3, normalize), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 rotate_x(float rad)", asMETHOD(vector3, rotate_x), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 rotate_x_deg(float deg)", asMETHOD(vector3, rotate_x_deg), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 rotate_y(float rad)", asMETHOD(vector3, rotate_y), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 rotate_y_deg(float deg)", asMETHOD(vector3, rotate_y_deg), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 rotate_z(float rad)", asMETHOD(vector3, rotate_z), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 rotate_z_deg(float deg)", asMETHOD(vector3, rotate_z_deg), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "bool zero_distance()", asMETHOD(vector3, zero_distance), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 dir_to( vector2 &in)", asMETHODPR(vector3, dir_to, (const vector2&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 dir_to( vector3 &in)", asMETHODPR(vector3, dir_to, (const vector3&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 dir_to_2d( vector2 &in)", asMETHODPR(vector3, dir_to_2d, (const vector2&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 dir_to_2d( vector3 &in)", asMETHODPR(vector3, dir_to_2d, (const vector3&) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

    retCode = engine->RegisterObjectMethod("vector3", "vector3 lerp( vector3 &in, float percent)", asMETHODPR(vector3, lerp, (const vector3&, const float), vector3), asCALL_THISCALL); assert(retCode >= 0);
    retCode = engine->RegisterObjectMethod("vector3", "vector3 slerp( vector3 &in, float percent)", asMETHODPR(vector3, slerp, (const vector3&, const float) const, vector3), asCALL_THISCALL); assert(retCode >= 0);

}

void register_vectors(asIScriptEngine*& engine)
{
    if (strstr(asGetLibraryOptions(), "AS_MAX_PORTABILITY"))
        register_vectors_generic(engine);
    else
        register_vectors_native(engine);
}