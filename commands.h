#pragma once
#include "configuration.h"

char buffer[16];
int bufPos = 0;

class CommandsProcessor {
public:
	CommandsProcessor(Serial &serial, Configuration &conf): serial(serial), conf(conf) {}

	void start() {
		serial.read((uint8_t*) buffer + bufPos, 1, callback(this, &CommandsProcessor::process));
	}

private:
	Serial &serial;
	Configuration &conf;

	void process(int flags) {
		if(buffer[bufPos] == '\n' || buffer[bufPos] == '\r') {
			buffer[bufPos] = '\0';
			char* args[MAX_CMD_ARGS];

			char *tok = strtok(buffer, " ");
			char *cmd = tok;

			int i = 0;
			while(tok && i < MAX_CMD_ARGS) {
				args[i] = tok = strtok(NULL, " ");
				i++;
			}

			run(cmd, i - 1, args);
			bufPos = 0;
		} else {
			bufPos = (bufPos + 1) % sizeof(buffer);
		}

		start();
	}

	void run(const char* cmd, int argc, char** argv) {
		if(strcmp(cmd, "mode") == 0 && argc >= 1) {
			if(strcmp(argv[0], "stop") == 0) {
				conf.state = STATE_STOP;
			} else if(strcmp(argv[0], "balance") == 0) {
				conf.state = STATE_BALANCE;
			} else if(strcmp(argv[0], "demo") == 0) {
				conf.state = STATE_DEMO;
			} else {
				//printf("Unknown mode\n");
			}
		} else if(strcmp(cmd, "demo_clear") == 0) {
			conf.positions.clear();
		} else if(strcmp(cmd, "demo_add") == 0 && argc >= 2) {
			Vectorf v;
			v.x = atof(argv[0]);
			v.y = atof(argv[1]);
			conf.positions.add(v);
		} else if(strcmp(cmd, "set_p")  == 0 && argc >= 1) {
			conf.const_p = atof(argv[0]);
		} else if(strcmp(cmd, "set_k")  == 0 && argc >= 1) {
			conf.const_k = atof(argv[0]);
		} else if(strcmp(cmd, "enable_servos") == 0 && argc >= 1) {
			conf.enabledServos = atoi(argv[0]);
		} else if(strcmp(cmd, "usx") == 0 && argc >= 1) {
			conf.state = STATE_STOP;
			conf.USX = atof(argv[0]);
		} else if(strcmp(cmd, "usy") == 0 && argc >= 1) {
			conf.state = STATE_STOP;
			conf.USY = atof(argv[0]);
		}
	}
};
