#ifndef __CLASS_COMMANDLINE_H
#define __CLASS_COMMANDLINE_H

#include <vector>
#include <string>
#include <iostream>
#include <string_algorithm.h>

class CommandLine {
    public:    
    typedef std::vector<std::string> tokenList;
    
    private:
    std::ostream &_out;
    std::istream &_in;

    std::string _prompt;
    std::string _unkcmd_err;

    bool running;
    int retcode;
    
    public:
    CommandLine(std::ostream &__out, std::istream &__in, const std::string &__prompt)
    : _out(__out)
    , _in(__in)
    , running(true)
    , retcode(0)
    , _prompt(__prompt)
    , _unkcmd_err("Unknown Command")
    { }
    
    std::ostream &out() { return _out; };
    std::istream &in() { return _in; };
    
    const std::string &prompt() { return _prompt; };
    void prompt(const std::string &s) { _prompt = s; };
    
    const std::string &unkerr_cmd() { return _unkcmd_err; };
    void unkcmd_err(const std::string &s) { _unkcmd_err = s; };
    
    virtual void showPrompt() { _out << _prompt; }
    
    virtual int onGo() { return 0; };
    virtual int onExit() { return 0; };
    
    virtual void onUnknownCommand(const std::string &input) { _out << _unkcmd_err << std::endl; };
    
    virtual int onCommand(const std::string &input)
    {
		static tokenList tokens;
        
        tokens.clear();
        
		parse(input, tokens);
    
		return onCommand(input, tokens);
    }
    
    virtual int onCommand(const std::string &input, const tokenList &tokens) { return -1; };
    
    virtual int onException(std::exception &e, const std::string &input)
    {
        _out << "Exception: input=[" << input << "]" << std::endl;
        _out << e.what() << std::endl;
    }
    
	void stop() { running = false; };
	
	int go(int argc, char *argv[])
	{
		std::string startup;
		if(argc >= 2)
		{
			startup = argv[1];
			for(size_t i=2;i<argc;i++)
			{
				startup += ' ';
				startup += argv[i];
			}
		}
		go(startup);
	}

	int go(const std::string &startup = std::string())
    {
        int retcode = onGo();
        if(retcode < -1)
            return retcode;
            
		std::string input;
        input.reserve(1024);
        if(startup.length())
            input = startup;
        else 
        {
            showPrompt();
            std::getline(_in, input);
        }
    
        tokenList tokens;
        while(!_in.eof())
        {
            try {
                
                if(onCommand(input) == -1)
                    onUnknownCommand(input);
                    
            } catch(std::exception &e)
            {
                onException(e, input);
            }
            
            if(!running)
                break;
                
            showPrompt();
			std::getline(_in, input);
        }
        
        return onExit();
    }
    
	virtual void parse(const std::string &in, tokenList &tokens)
    {
		static const std::string &whitespace = std::string(" \t\n");

        ::parse(in, tokens, whitespace);
    }
};

#endif
