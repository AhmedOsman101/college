#!/usr/bin/env bash

set -euo pipefail

trap 'exit 1' SIGUSR1

# ---  Main script logic --- #
clangc utils.c "$*"
