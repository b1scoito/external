#pragma once

// From: https://www.unknowncheats.me/forum/counterstrike-global-offensive/181308-external-convarfinder.html
class c_convar_manager
{
private:
	std::uintptr_t cvar_address = {};

public:
	c_convar_manager( const std::uintptr_t cvar = {} )
	{
		this->cvar_address = cvar;
	};

	~c_convar_manager() = default;

	constexpr auto& get_pointer() const
	{
		return this->cvar_address;
	}

	const int get_flags() const
	{
		return g_memory->read<std::int32_t>( this->cvar_address + 0x14 );
	}

	const std::string get_default_value() const
	{
		auto convar_default_value = std::make_unique<char[]>( 255 );

		if ( g_memory->read( g_memory->read<int>( this->cvar_address + 0x20 ), convar_default_value.get(), 255 ) )
			return convar_default_value.get();

		return {};
	}

	const std::string get_string() const
	{
		auto convar_string = std::make_unique<char[]>( 255 );

		if ( g_memory->read( g_memory->read<int>( this->cvar_address + 0x24 ), convar_string.get(), 255 ) )
			return convar_string.get();

		return {};
	}

	const float get_float() const
	{
		return g_memory->read<float>( this->cvar_address + 0x2C );
	}

	const std::int32_t get_int() const
	{
		return g_memory->read<std::int32_t>( this->cvar_address + 0x30 );
	}

public: // Write
	const void set_value( std::string value ) const
	{
		g_memory->write( g_memory->read<std::uintptr_t>( this->cvar_address + 0x24 ), value.data(), 255 );
	}

	const void set_value( float value ) const
	{
		g_memory->write<float>( this->cvar_address + 0x2C, value );
	}

	const void set_value( std::int32_t value ) const
	{
		g_memory->write<std::int32_t>( this->cvar_address + 0x30, value );
	}
};

inline std::map<std::string, std::uintptr_t> g_convar_list = {};

class c_convar : private c_convar_manager
{
public: // Read
	void populate_list()
	{
		const auto convar_hash_table = g_memory->read<std::uintptr_t>( sdk::base->get_vstdlib_image().base + sdk::offsets::interface_engine_cvar );
		const auto convar_list = g_memory->read<std::int32_t>( convar_hash_table + 0x34 );

		auto hash_map_entry = g_memory->read<std::int32_t>( convar_list );

		while ( hash_map_entry )
		{
			auto read_convar_name = std::make_unique<char[]>( 255 );

			const auto convar_address = g_memory->read<std::uintptr_t>( hash_map_entry + 0x4 );
			const auto convar_address_name = g_memory->read<std::uintptr_t>( convar_address + 0xC );

			if ( g_memory->read( convar_address_name, read_convar_name.get(), 255 ) )
				g_convar_list[read_convar_name.get()] = convar_address;

			hash_map_entry = g_memory->read<std::int32_t>( hash_map_entry + 0x4 );
		}
	}

	c_convar_manager find( std::string_view convar_name )
	{
		auto it = g_convar_list.find( convar_name.data() );
		if ( it == g_convar_list.end() )
			return {};

		return c_convar_manager(it->second);
	}
};

inline auto g_convar = std::make_unique<c_convar>();