/**
 * @file connector.h
 *
 * Class for creating client-side streaming connections.
 *
 * @author	Frank Pagliughi
 * @author	SoRo Systems, Inc.
 * @author  www.sorosys.com
 *
 * @date	December 2014
 */

// --------------------------------------------------------------------------
// This file is part of the "sockpp" C++ socket library.
//
// Copyright (c) 2014-2017 Frank Pagliughi
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
// IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// --------------------------------------------------------------------------

#ifndef __sockpp_connector_h
#define __sockpp_connector_h

#include "sockpp/stream_socket.h"
#include "sockpp/sock_address.h"

namespace sockpp {

/////////////////////////////////////////////////////////////////////////////

/**
 * Class to create a client stream connection.
 * This is a streaming socket, like a TCP socket.
 */
class connector : public stream_socket
{
	// Non-copyable
	connector(const connector&) =delete;
	connector& operator=(const connector&) =delete;

public:
	/**
	 * Creates an unconnected connector.
	 */
	connector() {}
	/**
	 * Creates the connector and attempts to connect to the specified
	 * address.
	 * @param addr The remote server address. 
	 */
	connector(const sock_address& addr);
	/**
	 * Determines if the socket connected to a remote host.
	 * Note that this is not a reliable determination if the socket is
	 * currently connected, but rather that an initial connection was
	 * established.
	 * @return @em true If the socket connected to a remote host,
	 *  	   @em false if not.
	 */
	bool is_connected() const { return is_open(); }
	/**
     * Attempts to connect to the specified server.
     * If the socket is currently connected, this will close the current
     * connection and open the new one.
	 * @param addr The remote server address.
	 * @return @em true on success, @em false on error
	 */
	bool connect(const sock_address& addr);
};

/////////////////////////////////////////////////////////////////////////////

/**
 * Class to create a client TCP connection.
 */
template <typename STREAM_SOCK, typename ADDR=typename STREAM_SOCK::addr_t>
class connector_tmpl : public connector
{
    /** The base class */
	using base = connector;

	// Non-copyable
	connector_tmpl(const connector_tmpl&) =delete;
	connector_tmpl& operator=(const connector_tmpl&) =delete;

public:
	/** The type of streaming socket from the acceptor. */
	using stream_sock_t = STREAM_SOCK;
	/** The type of address for the connector. */
	using addr_t = ADDR;

	/**
	 * Creates an unconnected connector.
	 */
	connector_tmpl() {}
	/**
	 * Creates the connector and attempts to connect to the specified
	 * address.
	 * @param addr The remote server address.
	 */
	connector_tmpl(const addr_t& addr) { connect(addr); }
	/**
	 * Gets the local address to which the socket is bound.
	 * @return The local address to which the socket is bound.
	 * @throw sys_error on error
	 */
	addr_t address() const { return addr_t(base::address()); }
	/**
	 * Gets the address of the remote peer, if this socket is connected.
	 * @return The address of the remote peer, if this socket is connected.
	 * @throw sys_error on error
	 */
	addr_t peer_address() const { return addr_t(base::peer_address()); }
	/**
	 * Attempts to connects to the specified server.
	 * If the socket is currently connected, this will close the current
	 * connection and open the new one.
	 * @param addr The remote server address.
	 * @return @em true on success, @em false on error
	 */
	bool connect(const addr_t& addr) { return base::connect(addr); }
};

/////////////////////////////////////////////////////////////////////////////
// end namespace sockpp
}

#endif		// __sockpp_connector_h

