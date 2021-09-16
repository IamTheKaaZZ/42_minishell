#!/bin/sh

echo "Do you want to check if the updated readline library is installed?"
bash scripts/yesno.sh
if [[ $? != 0 ]] ; then
	exit
fi

#	CHECK IF BREW IS INSTALLED
which -s brew
if [[ $? != 0 ]] ; then
    echo "Installing Homebrew..."
	bash scripts/yesno.sh
	if [[ $? != 0 ]] ; then
		exit
	else
		ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
	fi
else
	echo "Updating brew..."
	bash scripts/yesno.sh
	if [[ $? == 0 ]] ; then
		brew update
	fi
fi

#	CHECK if the config is in zshrc
if grep 'source $HOME/.brewconfig.zsh' ~/.zshrc ; then
	echo "zshrc is configured correctly."
else
	echo "Adding config to .zshrc..."
	bash scripts/yesno.sh
	if [[ $? != 0 ]] ; then
		exit
	else
		echo 'source $HOME/.brewconfig.zsh' >> ~/.zshrc
		source ~/.zshrc
	fi
fi

#	CHECK IF pkg-config and readline are installed

if brew list | grep pkg-config ; then
	echo "OK!"
else
	echo "pkg-config not found, installing..."
	bash scripts/yesno.sh
	if [[ $? != 0 ]] ; then
		exit
	else
		brew install pkg-config
	fi
fi

if brew list | grep readline ; then
	echo "OK!"
else
	echo "readline not found, please run..."
	bash scripts/yesno.sh
	if [[ $? != 0 ]] ; then
		exit
	else
		brew install readline
	fi
fi

printenv PKG_CONFIG_PATH
if [[ $? != 0 ]] ; then
    echo "Environment variable is not set correctly..."
	RL_PATH=$(brew ls readline | grep readline.pc | sed 's|/readline.pc||g')
	echo "Please run: export PKG_CONFIG_PATH=$RL_PATH"
else
    echo "Environment variable OK"
fi

echo "The Makefile should compile correctly now."