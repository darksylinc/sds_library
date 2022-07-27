// Copyright (c) 2018-present Art of the State LLC
// Under MIT License. See LICENSE.md for details

#pragma once

#include <limits>
#include <string>

namespace sds
{
	/// Returns true if s1 > s2, checks for wrap-around.
	template <typename T>
	static bool isSequenceMoreRecent( T s1, T s2 )
	{
		// clang-format off
		const T max = std::numeric_limits<T>::max();
		return
			( ( s1 > s2 ) &&
			  ( s1 - s2 <= (max >> 1u) ) )
			   ||
			( ( s2 > s1 ) &&
			  ( s2 - s1  > (max >> 1u) ) );
		// clang-format on
	}

	/// Performs the same as std::bit_cast
	/// i.e. the same as reinterpret_cast but without breaking strict aliasing rules
	template <class Dest, class Source>
#if defined __has_builtin && __has_builtin( __builtin_bit_cast )
	constexpr
#else
	inline
#endif
		Dest
		bit_cast( const Source &source )
	{
#if defined __has_builtin && __has_builtin( __builtin_bit_cast )
		return __builtin_bit_cast( Dest, source );
#else
		static_assert( sizeof( Dest ) == sizeof( Source ),
					   "bit_cast requires source and destination to be the same size" );
		static_assert( std::is_trivially_copyable<Dest>::value,
					   "bit_cast requires the destination type to be copyable" );
		static_assert( std::is_trivially_copyable<Source>::value,
					   "bit_cast requires the source type to be copyable" );
		Dest dest;
		memcpy( &dest, &source, sizeof( dest ) );
		return dest;
#endif
	}
}  // namespace sds
