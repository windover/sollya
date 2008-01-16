#!/bin/sh
touch ChangeLog
autoreconf --force --install -s -I config -I m4
