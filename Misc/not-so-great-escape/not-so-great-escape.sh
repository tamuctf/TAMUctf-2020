#!/bin/sh

chroot_dir=$(mktemp -d)

function cleanup {
  rm -rf ${chroot_dir}
}
trap cleanup EXIT

read -sp "Password: " password
echo

if [[ -z "${password}" || "2ff6b0b9733a294cb0e0aeb7269dea5ae05d2a2de569e8464b5967c6c207548e" != "${password}" ]]; then
  echo -e "Bad password. Exiting."
  exit 1
fi

cp -r /pwn/jail/* ${chroot_dir}

cp /etc/apk/repositories ${chroot_dir}/etc/apk/repositories
cp /etc/resolv.conf ${chroot_dir}/etc/resolv.conf

chroot ${chroot_dir}
