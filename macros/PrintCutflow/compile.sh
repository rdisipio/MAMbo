#!/bin/bash

g++ `root-config --cflags --libs` main.C CutflowPrinter.C  -g -o PrintCutflow

