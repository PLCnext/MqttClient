//
// Copyright (c) Phoenix Contact GmbH & Co. KG. All rights reserved.
// Licensed under the MIT. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT
//
#include "Client.hpp"

namespace PxceTcs { namespace Mqtt
{

Client::Client()
{
    return;
}

void Client::Connect(Client::client_id_t clientId)
{
	try
    {
		this->clients.at(clientId)->connect();
	}
	catch (...)
    {
        throw;
	}
}

void Client::Connect(Client::client_id_t clientId, mqtt::connect_options opts)
{
	try
    {
		this->clients.at(clientId)->connect(opts);
	}
	catch (...)
    {
        throw;
	}
}

Client::client_id_t Client::CreateClient(const std::string serverURI, const std::string clientId)
{
    Client::client_id_t clientKey = -1;
    bool insert_result = false;

	try
    {
        // TODO: Check if there are already the maximum number of elements in the container

        std::srand(std::time(nullptr)); // use current time as seed for random generator

        auto client = std::make_shared<mqtt::client>(serverURI, clientId);

        do
        {
            // Generate a random number as the container key
            // This helps (in only a small way) to avoid clients "guessing" the id of other clients
            // The modulo operation limits this value to the allowed range
            clientKey = std::rand() % std::numeric_limits< Client::client_id_t >::max() + 1;

            // Try inserting a new client object at this location (note that we're currently limited to C++11 functions)
            insert_result = this->clients.insert(std::make_pair(clientKey, client)).second;

            // TODO: Limit the maximum number of iterations of this loop, just in case ...
        } while (insert_result == false);
    }
	catch (...)
    {
        throw;
	}
    return clientKey;
}

void Client::DestroyClient(Client::client_id_t clientId)
{
	try
    {
        // Erase the client object from the container
        this->clients.erase(clientId);
	}
	catch (...)
    {
        throw;
	}
}

void Client::Disconnect(Client::client_id_t clientId)
{
	try
    {
        this->clients.at(clientId)->disconnect();
    }
	catch (...)
    {
        throw;
	}
}

void Client::Disconnect(Client::client_id_t clientId, int timeoutMS)
{
	try
    {
        this->clients.at(clientId)->disconnect(timeoutMS);
    }
	catch (...)
    {
        throw;
	}
}

bool Client::IsConnected(Client::client_id_t clientId)
{
    bool result = false;

    try
    {
        result = this->clients.at(clientId)->is_connected();
    }
	catch (...)
    {
        throw;
	}
    return result;
}

void Client::Publish(Client::client_id_t clientId, mqtt::string_ref top, const void * payload, std::size_t n, int qos, bool retained)
{
    try
    {
        this->clients.at(clientId)->publish(top, payload, n, qos, retained);
    }
	catch (...)
    {
        throw;
	}
}

void Client::Reconnect(Client::client_id_t clientId)
{
	try
    {
        this->clients.at(clientId)->reconnect();
    }
	catch (...)
    {
        throw;
	}
}

void Client::Subscribe(Client::client_id_t clientId, const std::string & topicFilter)
{
	try
    {
        this->clients.at(clientId)->subscribe(topicFilter);
    }
	catch (...)
    {
        throw;
	}
}

bool Client::TryConsumeMessage(Client::client_id_t clientId, mqtt::const_message_ptr * msg)
{
    bool result = false;

	try
    {
        result = this->clients.at(clientId)->try_consume_message(msg);
    }
	catch (...)
    {
        throw;
	}
    return result;
}

void Client::UnSubscribe(Client::client_id_t clientId, const std::string & topicFilter)
{
	try
    {
        this->clients.at(clientId)->unsubscribe(topicFilter);
    }
	catch (...)
    {
        throw;
	}
}

}} // end of namespace PxceTcs.Mqtt
