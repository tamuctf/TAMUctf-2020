from angr import *
from claripy import *


proj = Project('angrmanagement', load_options={ 'auto_load_libs': False, 'main_opts': {'base_addr': 0x0}})

x = BVS('x', 32 * 8)
state = proj.factory.blank_state(stdin=x)



# constrain to printable characters
def char(state, byte):
    return state.solver.And(byte <= '~', byte >= ' ')

for c in x.chop(8):
    state.solver.add(char(state, c))

sm = proj.factory.simulation_manager(state)


sm.explore(find=0x2264, avoid=0x22b6)

if sm.found:
    for i in sm.found:
        print(str(i.solver.eval(x, cast_to=bytes)))