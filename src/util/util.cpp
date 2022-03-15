/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2022, Regents of the University of California.
 *
 * This file is part of NDNS (Named Data Networking Domain Name Service).
 * See AUTHORS.md for complete list of NDNS authors and contributors.
 *
 * NDNS is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NDNS is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NDNS, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "util.hpp"
#include "config.hpp"

#include <ndn-cxx/security/transform/base64-encode.hpp>
#include <ndn-cxx/security/transform/buffer-source.hpp>
#include <ndn-cxx/security/transform/stream-sink.hpp>

namespace ndn {
namespace ndns {

std::string
getDefaultDatabaseFile()
{
  return NDNS_DEFAULT_DBFILE;
}

NdnsContentType
toNdnsContentType(const std::string& str)
{
  if (str == "resp")
    return NDNS_RESP;
  else if (str == "nack")
    return NDNS_NACK;
  else if (str == "auth")
    return NDNS_AUTH;
  else if (str == "blob")
    return NDNS_BLOB;
  else if (str == "link")
    return NDNS_LINK;
  else if (str == "key")
    return NDNS_KEY;
  else
    return NDNS_UNKNOWN;
}

void
output(const Data& data, std::ostream& os, bool isPretty)
{
  using security::transform::base64Encode;
  using security::transform::bufferSource;
  using security::transform::streamSink;

  const Block& block = data.wireEncode();
  if (!isPretty) {
    bufferSource(block) >> base64Encode() >> streamSink(os);
  }
  else {
    os << "Name: " << data.getName() << std::endl;
    auto kl = data.getKeyLocator();
    if (kl) {
      os << "KeyLocator: " << kl->getName() << std::endl;
    }
    bufferSource(block) >> base64Encode() >> streamSink(os);
    os << std::endl;
  }
}

} // namespace ndns
} // namespace ndn
