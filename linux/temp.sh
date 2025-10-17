#!/usr/bin/env bash

set -eo pipefail
trap 'exit 1' SIGUSR1

# ---  Main script logic --- #
mainloop() {
  while (($(cpu-usage | cut -d'.' -f1) < 60)); do
    :
  done

  killwait "$(pidof vhs)"
}

for file in output/*.mp4; do
  log-info "${file} started"
  ffmpeg -hide_banner -i "${file}" -vf "fps=15,scale=1280:-1:flags=lanczos,palettegen" -y palette.png
  ffmpeg -hide_banner -i "${file}" -i palette.png -filter_complex "fps=15,scale=1280:-1:flags=lanczos[x];[x][1:v]paletteuse" -y "${file}.gif"
  log-info "${file} finished"
done
