#pragma once
#include "configuration.h"


char buffer[128];

class CommandsProcessor {
public:
	CommandsProcessor(Serial &serial, Configuration &conf): serial(serial), conf(conf) {}

	void start() {
		serial.read((uint8_t*) buffer, sizeof(buffer), callback(this, &CommandsProcessor::process), SERIAL_EVENT_RX_COMPLETE, '\n');
	}

private:
	Serial &serial;
	Configuration &conf;

	void process(int flags) {
		char* end = (char*) memchr(buffer, '\n', sizeof(buffer));
		char* args[MAX_CMD_ARGS];
		if(end) {
			*end = '\0';
			char *tok = strtok(buffer, " ");
			char *cmd = tok;

			int i = 0;
			while(tok && i < MAX_CMD_ARGS) {
				args[i] = tok = strtok(NULL, " ");
			}

			run(cmd, i, args);
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
				printf("Unknown mode\n");
			}
		} else if(strcmp(cmd, "demo_clear") == 0) {
			conf.positions.clear();
		} else if(strcmp(cmd, "demo_add") == 0 && argc >= 2) {
			Vectorf v;
			v.x = atof(argv[0]);
			v.y = atof(argv[1]);
			conf.positions.add(v);
		} else {
			printf("Unknown cmd\n");
		}
	}
};
