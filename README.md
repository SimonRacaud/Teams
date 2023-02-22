# Teams
Linux TCP Socket - Messaging service

# Functionalities

- Creating/Joining/Leaving a team
- Creating a user
- Creating a channel in a team
- Creating a thread in a channel
- Creating a comment in a thread
- Saving & restoring users, teams, channels, threads & associated comments
- Personnal discussion (from a user to an other)
- Saving & restoring personnal discussion

# Commands

- /help : show help
- /login [“user_name”] : set the user_name used by client
- /logout : disconnect the client from the server
- /users : get the list of all users that exist on the domain
- /user [“user_uuid”] : get information about a user
- /send [“user_uuid”] [“message_body”] : send a message to a user
- /messages [“user_uuid”] : list all messages exchange with an user
- /subscribe [“team_uuid”] : subscribe to the event of a team and its sub directories (enable reception of all events from a team)
- /subscribed ?[“team_uuid”] : list all subscribed teams or list all users subscribed to a team
- /unsubscribe [“team_uuid”] : unsubscribe from a team
- /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : use specify a context team/channel/thread
- /create : based on what is being used create the sub resource (see below)
- /list : based on what is being used list all the sub resources (see below)
- /info : based on what is being used list the current (see below)

## Create command
When the context is not defined (/use):
- /create [“team_name”] [“team_description”] : create a new team
When team_uuid is defined (/use “team_uuid”):
- /create [“channel_name”] [“channel_description”] : create a new channel
When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
- /create [“thread_title”] [“thread_message”] : create a new thread
When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
- /create [“comment_body”] : create a new reply

## List command
When the context is not defined (/use):
- /list : list all existing teams
When team_uuid is defined (/use “team_uuid”):
- /list : list all existing channels
When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
- /list : list all existing threads
When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
- /list : list all existing replies

## Info command

When the context is not defined (/use):
- /info : display currently logged user infos
When team_uuid is defined (/use “team_uuid”):
- /info : display currently selected team infos
When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
- /info : display currently selected channel infos
When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
- /info : display currently selected thread infos

# Usage
`$> make`

`$> ./myteams_cli -h`
```
USAGE:	./myteams_cli ip port
	ip	is the server ip address on which the server socket listens
	port	is the port number on which the server socket listens
```

`$> ./myteams_server -h`
```
USAGE: ./myteams_server port
		port	is the port number on which the server socket listens.
```

# Academy

Mark 20 - Grade A/A
