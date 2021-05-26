#!/bin/bash
# ./test_myteams.sh | ./myteams_cli 127.0.0.1 8080 > /dev/null 2> /tmp/myteams_tests

DATABASE="database.myteams"
OUT=/tmp/myteams_tests
TAIL=`which tail`
TIMEOUT=1

get_id()
{
    local index=$1

    id=`$TAIL -n 1 $OUT | cut -d' ' -f $index`
}

is_valid_command()
{
    local str=$1
    local data=`$TAIL -n 1 $OUT | cat -e | grep "$str[$]$" | wc -l`

    return $data
}

print_failed()
{
    echo "$1 test failed" 1>&2
    echo "Expected : [$2$]" 1>&2
    echo "Received : ["`$TAIL -n 1 $OUT| cat -e`"]" 1>&2
    echo -e "\e[31mKO\e[0m" 1>&2
}

print_succeeded()
{
  echo "$1 test succeeded" 1>&2
  echo -e "\e[32mOK\e[0m" 1>&2
}

launch_test()
{
    local test_name=$1
    local cmd=$2
    local result=$3

    echo "$cmd"
    sleep $TIMEOUT
    is_valid_command "$result"
    if [[ ! $? -eq 1 ]]; then
        print_failed "$test_name" "$result"
        exit 1
    fi
}

# Simple authentication
test00()
{
    local test_name="Authentication"
    local username="yo"

    local cmd1="/login \"$username\""
    local result1="Client .* logged in with login $username"
    local cmd2="/logout"
    local result2="Client .* logged out with login $username"

    launch_test "$test_name" "$cmd1" "$result1"
    launch_test "$test_name" "$cmd2" "$result2"

    print_succeeded "$test_name"
}

# Create teams
test01()
{
    local test_name="Create teams"
    local username="yo"
    local team1="myTeam01"
    local team2="myTeam02"
    local team3="myTeam03"

    local cmd1="/login \"$username\""
    local result1="Client .* logged in with login $username"

    local cmd2="/use"
    local result2=""
    local cmd3="/create \"$team1\" \"bash\""
    local result3="New team created event id .*: $team1 (bash)"
    local cmd4="/create \"$team2\" \"bash\""
    local result4="New team created event id .*: $team2 (bash)"
    local cmd5="/create \"$team3\" \"bash\""
    local result5="New team created event id .*: $team3 (bash)"


    local cmd6="/logout"
    local result6="Client .* logged out with login $username"

    launch_test "$test_name" "$cmd1" "$result1"
    launch_test "$test_name" "$cmd2" "$result2"
    launch_test "$test_name" "$cmd3" "$result3"
    launch_test "$test_name" "$cmd4" "$result4"
    launch_test "$test_name" "$cmd5" "$result5"
    launch_test "$test_name" "$cmd6" "$result6"

    print_succeeded "$test_name"
}

send_private_message()
{
    # Parameters
    local test_name=$1
    local username1=$2
    local username2=$3
    local uuid1=$4
    local uuid2=$5
    local message=$6

    # User 1
    local cmd1="/login \"$username1\""
    local result1="Client $uuid1 logged in with login $username1"

    local cmd2="/send \"$uuid2\" \"$message\""
    local result2=""

    local cmd3="/logout"
    local result3="Client $uuid1 logged out with login $username1"

    # User 2
    local cmd4="/login \"$username2\""
    local result4="Client $uuid2 logged in with login $username2"

    local cmd5="/messages \"$uuid1\""
    local result5="\[Private\] $uuid1 .*: $message"

    local cmd6="/logout"
    local result6="Client $uuid2 logged out with login $username2"

    launch_test "$test_name" "$cmd1" "$result1"
    launch_test "$test_name" "$cmd2" "$result2"
    launch_test "$test_name" "$cmd3" "$result3"
    launch_test "$test_name" "$cmd4" "$result4"
    launch_test "$test_name" "$cmd5" "$result5"
    launch_test "$test_name" "$cmd6" "$result6"
}

# Send private message
test02()
{
    local test_name="Send private messages"
    local username1="yo"
    local username2="toi"

    # User 1
    local cmd1="/login \"$username1\""
    local result1="Client .* logged in with login $username1"
    local cmd2="/logout"
    local result2="Client .* logged out with login $username1"

    # User 2
    local cmd3="/login \"$username2\""
    local result3="Client .* logged in with login $username2"
    local cmd4="/logout"
    local result4="Client .* logged out with login $username2"

    launch_test "$test_name" "$cmd1" "$result1"
    get_id 2
    local sender=$id
    launch_test "$test_name" "$cmd2" "$result2"
    launch_test "$test_name" "$cmd3" "$result3"
    get_id 2
    local receiver=$id
    launch_test "$test_name" "$cmd4" "$result4"

    send_private_message "$test_name" "$username1" "$username2" "$sender" "$receiver" "Salut toi"
    send_private_message "$test_name" "$username2" "$username1" "$receiver" "$sender" "Comment tu vas ?"
    send_private_message "$test_name" "$username1" "$username2" "$sender" "$receiver" "Super et toi ?"
    send_private_message "$test_name" "$username2" "$username1" "$receiver" "$sender" "Niquel mgl !"

    print_succeeded "$test_name"
}

test00
test01
test02