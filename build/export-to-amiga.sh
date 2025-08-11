#!/usr/bin/env bash

# This scripts bundles together the DICE source code, Amiga NDK, and stage 1 bootstrap into an LhA archive, which can be unpacked
# on an Amiga where the remainder of the build can be completed.

set -euo pipefail

# Parse options - source: https://stackoverflow.com/a/14203146/1031460

POSITIONAL_ARGS=()
SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
BASE_DIR="$(dirname "$SCRIPT_DIR")"
OUTPUT="${BASE_DIR}/export-to-amiga.lha"

while [[ $# -gt 0 ]]; do
  case $1 in
    -o|--output)
      OUTPUT="$2"
      shift # past argument
      shift # past value
      ;;
    -*|--*)
      echo "Unknown option $1"
      exit 1
      ;;
    *)
      POSITIONAL_ARGS+=("$1") # save positional arg
      shift # past argument
      ;;
  esac
done

# Check we have exactly no positional arguments
if [[ ${#POSITIONAL_ARGS[@]} -ne 0 ]]; then
  echo "Usage: $0 [ --output <pathname> ]"
  exit 1
fi

# Create a temporary directory that we use as a staging area
tmpdir=$(mktemp -d) || { echo "Failed to create temporary directory"; exit 1; }
trap 'rm -rf "$tmpdir"' EXIT

# Use rsync to copy all the files to the temporary directory, excluding the stuff we don't want in the distribution
rsync -av \
  --exclude='.git' \
  --exclude='export-to-amiga.lha' \
  --exclude='bin' \
  --exclude='bin1-bootstrap' \
  --exclude='bin2' \
  --exclude='bin2-bootstrap' \
  --exclude='dlib' \
  --exclude='dlib1-bootstrap' \
  --exclude='dlib2' \
  --exclude='dlib2-bootstrap' \
  "${BASE_DIR}/" "${tmpdir}/DICE-nx"

# Put an Amiga icon in place
info_file="${BASE_DIR}.info"
if [ -f "${info_file}" ]; then
  cp "${info_file}" "${tmpdir}/DICE-nx.info"
else
  echo "Warning: No file found at ${BASE_DIR}/${info_file} for the directory icon, skipping."
fi

[ -f "${OUTPUT}" ] && rm "${OUTPUT}"

set -x
cd "${tmpdir}" && exec lha a "${OUTPUT}" *
