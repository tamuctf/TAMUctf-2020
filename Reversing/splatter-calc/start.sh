#!/bin/bash

socat -d -d tcp-l:60032,fork system:/usr/bin/splatter-calc