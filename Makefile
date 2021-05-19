##
## EPITECH PROJECT, 2021
## Project_2021
## File description:
## Project makefile
##

DSRC	=	./src/

SRC_UT 			= 	tests/tests_project.c											\
					src/utility/signal_manager.c									\
					src/utility/strdup_format.c										\
					src/utility/walloc.c											\
					src/network/request_create.c									\
					src/network/request_destroy.c									\
					src/network/request_parse.c										\
					src/network/request_write.c										\
					src/server/Database/factories/create_user.c						\
					src/server/Database/factories/create_private_msg.c				\
					src/server/Database/factories/create_thread.c					\
					src/server/Database/factories/create_channel.c					\
					src/server/Database/getter/get_team.c							\
					src/server/Database/getter/get_user.c							\
					src/server/Database/getter/get_thread.c							\
					src/server/Database/serializer/serializer_channel_t.c			\
					src/server/Database/serializer/serializer_private_msg_t.c		\
					src/server/Database/serializer/serializer_reply_t.c				\
					src/server/Database/serializer/serializer_team_t.c				\
					src/server/Database/serializer/serializer_thread_t.c			\
					src/server/Database/serializer/serializer_user_t.c				\
					src/server/Database/serializer/serializer_header_t.c			\
					src/server/Database/deserializer/deserializer_channel_t.c		\
					src/server/Database/deserializer/deserializer_private_msg_t.c	\
					src/server/Database/deserializer/deserializer_reply_t.c			\
					src/server/Database/deserializer/deserializer_team_t.c			\
					src/server/Database/deserializer/deserializer_thread_t.c		\
					src/server/Database/deserializer/deserializer_user_t.c			\
					src/server/Database/saver/saver.c								\
					src/server/Database/saver/create_empty_database_save_t.c		\
					src/server/Database/saver/create_database_save_t.c				\
					src/server/Database/saver/fill_data/fill_data_length.c			\
					src/server/Database/saver/fill_data/run_fill_data.c				\
					src/server/Database/saver/fill_data/get_nb_team_from_user.c		\
					src/server/Database/loader/loader.c								\
					src/server/Database/loader/convert_database.c					\
					src/server/Database/loader/read_channels.c						\
					src/server/Database/loader/read_private_msg.c					\
					src/server/Database/loader/read_replies.c						\
					src/server/Database/loader/read_teams.c							\
					src/server/Database/loader/read_threads.c						\
					src/server/Database/loader/read_users.c							\

SRC_FILES_CLI	=	client/main.c							\
					client/destroy/app_destroy.c			\
					client/init/app_init.c					\
					client/init/connect_to_server.c			\
					client/init/parse_args.c				\
					client/loop/app_loop.c					\
					client/loop/process_read.c				\
					client/loop/process_write.c				\
					client/loop/prompt.c					\
					client/logger/logger.c					\
					utility/is_ip.c							\
					utility/is_number.c						\
					utility/signal_manager.c				\
					utility/walloc.c						\
					utility/strdup_format.c					\
					utility/strconcat.c						\
					network/request_create.c				\
					network/request_destroy.c				\
					network/request_write.c					\
					network/response_destroy.c				\
					network/response_read.c					\
					network/request_push.c					\

SRC_FILES_SRV	= 	server/main.c												\
					utility/signal_manager.c									\
					utility/strdup_format.c										\
					utility/walloc.c											\
					utility/is_number.c											\
					utility/strconcat.c											\
					server/app/app_create.c										\
					server/app/app_destroy.c									\
					server/app/app_loop.c										\
					server/app/app_select.c										\
					server/app/client.c											\
					server/app/process_request.c								\
					server/request/request_execute.c							\
					network/request_create.c									\
					network/request_destroy.c									\
					network/request_parse.c										\
					network/request_write.c										\
					network/response_create.c									\
					network/response_destroy.c									\
					network/response_read.c										\
					network/response_send.c										\
					network/body/body_maker_team.c								\
					network/body/body_maker_channel.c							\
					network/body/body_maker_user.c								\
					network/body/body_maker_private_msg.c						\
					network/body/body_maker_reply.c								\
					network/body/body_maker_thread.c							\
					server/Database/factories/create_team.c						\
					server/Database/factories/create_user.c						\
					server/Database/factories/create_reply.c					\
					server/Database/factories/create_thread.c					\
					server/Database/factories/create_channel.c					\
					server/Database/factories/create_private_msg.c				\
					server/Database/getter/get_team.c							\
					server/Database/getter/get_user.c							\
					server/Database/getter/get_reply.c							\
					server/Database/getter/get_thread.c							\
					server/Database/getter/get_channel.c						\
					server/Database/getter/get_private_msg.c					\
					server/Database/updater/user_subscription_add.c				\
					server/Database/updater/user_subscription_remove.c			\
					server/Database/serializer/serializer_channel_t.c			\
					server/Database/serializer/serializer_private_msg_t.c		\
					server/Database/serializer/serializer_reply_t.c				\
					server/Database/serializer/serializer_team_t.c				\
					server/Database/serializer/serializer_thread_t.c			\
					server/Database/serializer/serializer_user_t.c				\
					server/Database/serializer/serializer_header_t.c			\
					server/Database/deserializer/deserializer_channel_t.c		\
					server/Database/deserializer/deserializer_private_msg_t.c	\
					server/Database/deserializer/deserializer_reply_t.c			\
					server/Database/deserializer/deserializer_team_t.c			\
					server/Database/deserializer/deserializer_thread_t.c		\
					server/Database/deserializer/deserializer_user_t.c			\
					server/Database/saver/fill_data/fill_data_length.c			\
					server/Database/saver/fill_data/run_fill_data.c				\
					server/Database/saver/fill_data/get_nb_team_from_user.c		\
					server/Database/saver/create_database_save_t.c				\
					server/Database/saver/saver.c								\
					server/Database/saver/create_empty_database_save_t.c		\
					server/Database/loader/loader.c								\
					server/Database/loader/convert_database.c					\
					server/Database/loader/read_channels.c						\
					server/Database/loader/read_private_msg.c					\
					server/Database/loader/read_replies.c						\
					server/Database/loader/read_teams.c							\
					server/Database/loader/read_threads.c						\
					server/Database/loader/read_users.c							\

SRC_CLI	=	$(addprefix $(DSRC), $(SRC_FILES_CLI))
SRC_SRV	=	$(addprefix $(DSRC), $(SRC_FILES_SRV))

OBJ_CLI	=	$(SRC_CLI:.c=.o)
OBJ_SRV	=	$(SRC_SRV:.c=.o)

NAME_CLI	=	myteams_cli
NAME_SRV	=	myteams_server
NAME_UT 	=	test.out

INCLUDE = -I./include -I./libs/myteams -I./libs/socket/include -I./libs/
CFLAGS	+= -Wall -Wextra -W $(INCLUDE) #-Werror

LD_FLAGS += -lmysocket -L./libs/socket -lmyteams -L./libs/myteams -luuid

all:  client server
	ln -sf ./libs/myteams/libmyteams.so libmyteams.so

client: CFLAGS += -I./include/client
client: $(OBJ_CLI)
	make -C libs/socket
	@$(CC) -o $(NAME_CLI) $(OBJ_CLI) $(LD_FLAGS) -Wl,-rpath=$(PWD) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME_CLI)\n"$(DEFAULT) || \
		($(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME_CLI)\n"$(DEFAULT) && exit 1)

server: CFLAGS += -I./include/server
server: $(OBJ_SRV)
	make -C libs/socket
	@$(CC) -o $(NAME_SRV) $(OBJ_SRV) $(LD_FLAGS) -Wl,-rpath=$(PWD) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME_SRV)\n"$(DEFAULT) || \
		($(ECHO) $(BOLD_T)$(RED_C)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME_SRV)\n"$(DEFAULT) && exit 1)

clean:
	make clean -C libs/socket
	$(RM) -f  $(OBJ_CLI) $(OBJ_SRV)
	@$(RM) -f *.gcda
	@$(RM) -f *.gcno

fclean:	clean
	$(RM) -f $(NAME_CLI) $(NAME_SRV) $(NAME_UT)

re:	fclean all

tests_run: INCLUDE += -I./include/server
tests_run:
	gcc -o $(NAME_UT) $(SRC_UT) $(INCLUDE) -lcriterion --coverage -luuid && ./$(NAME_UT)

coverage:
	@gcovr -r . --exclude-directories tests
	@gcovr -b --exclude-directories tests

debug: CFLAGS += -g
debug: re

.PHONY:	client server clean fclean re tests_run coverage debug

ECHO	=	/bin/echo -e
DEFAULT	=	"\e[0m"
BOLD_T	=	"\e[1m"
DIM_T	=	"\e[2m"
UNDLN_T	=	"\e[4m"
BLACK_C	=	"\e[30m"
RED_C	=	"\e[31m"
GREEN_C	=	"\e[32m"
YELLO_C	=	"\e[33m"
BLUE_C	=	"\e[34m"
MAGEN_C	=	"\e[35m"
CYAN_C	=	"\e[36m"
WHITE_C	=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LINE_RETURN	=	$(ECHO) ""
