/*
  Copyright (c) 2011, The Mineserver Project
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of the The Mineserver Project nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <boost/lexical_cast.hpp>

#include <mineserver/game.h>
#include <mineserver/network/client.h>
#include <mineserver/network/message.h>
#include <mineserver/network/message/blockplacement.h>

#include <mineserver/watcher/blockplacement.h>

void Mineserver::Watcher_BlockPlacement::operator()(Mineserver::Game::pointer_t game, Mineserver::Network_Client::pointer_t client, Mineserver::Network_Message::pointer_t message) const
{
  std::cout << "Block-placement watcher called!" << std::endl;
  const Mineserver::Network_Message_BlockPlacement* msg = reinterpret_cast<Mineserver::Network_Message_BlockPlacement*>(&(*message));

  //if (msg->itemId==-1) { return; }

  Mineserver::World::pointer_t world = game->getWorld(0);

  int chunk_x, chunk_z;
  chunk_x = msg->x / 16;
  chunk_z = msg->z / 16;

  if (!world->hasChunk(chunk_x, chunk_z))
  {
    std::cout << "Chunk " << chunk_x << "," << chunk_z << " not found!" << std::endl;
  }
  else
  {
    Mineserver::World_Chunk::pointer_t chunk = world->getChunk(chunk_x, chunk_z);
    
    int x, y, z, type;
    x = msg->x;
    y = msg->y;
    z = msg->z;
    type = chunk->getBlockType(x, y, z);

    std::string text = "§4You interacted with block id ";
    text += boost::lexical_cast<std::string>(type) + " at ";
    text += boost::lexical_cast<std::string>(x) + ",";
    text += boost::lexical_cast<std::string>(y) + ",";
    text += boost::lexical_cast<std::string>(z) + "!";
	  game->chat(client, text, game->chatSelf);

    // (TODO) interpret block action

  }
}

