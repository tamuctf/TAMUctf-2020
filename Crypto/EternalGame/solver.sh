#!/bin/bash

if ! command -v hashpump | grep -q "hashpump"; then
  echo -e "You need hashpump to do this"
  exit 1
fi

echo -e "Getting base hash..."

high_score=653086069891774904466108141306028536722619133804
base_hash=$((echo 1; echo 3; echo 3) | socat - tcp:172.17.0.2:8812 | tail -n 4 | head -n 1)
key_size=0

echo -e "Discovered base hash of $base_hash"
echo -e "Bruting for key size..."

for i in {1..50}; do
  if (echo "2"; printf '%b\n' "$(hashpump -s ${base_hash} -d 1 -a 1 -k ${i})" | tac; echo "3") | socat - tcp:172.17.0.2:8812 | tail -n 4 | head -n 1 | grep -q "better"; then
    echo -e "Discovered key size of $i, continuing..."
    key_size=$i
    break
  fi
done

echo -e "Beginning brute to overcome the size..."

for i in {1..100}; do
  out=$((echo "2"; printf '%b\n' "$(hashpump -s ${base_hash} -d 1 -a $(python3 -c 'print('${high_score}'+'${i}')') -k ${key_size})" | tac; echo "3") | socat - tcp:172.17.0.2:8812)
  if echo "$out" | grep -q "gigem"; then
    echo "$out" | grep "gigem"
    break
  fi
done
