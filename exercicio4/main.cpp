/******************************************************
 * This is the main file for the mips1 ArchC model    *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/

// Rodolfo editou aqui
//
const char *project_name="mips";
const char *project_file="mips1.ac";
const char *archc_version="2.0beta1";
const char *archc_options="-abi -dy ";

#include <systemc.h>
#include "mips.H"
#include "memory.h"
#include "peripheral.h"
#include "bus.h"

int sc_main(int ac, char *av[])
{

  //!  ISA simulator
  mips mips_proc1("mips");

  //criando outro processador
  mips mips_proc2("mips");

  //! Bus
  ac_tlm_bus bus("bus");
  // Memory
  ac_tlm_mem mem("mem");
  // Peripheral
  ac_tlm_peripheral peripheral("peripheral");

#ifdef AC_DEBUG
  ac_trace("mips1_proc1.trace");
#endif

  mips_proc1.DM(bus.target_export);
  mips_proc2.DM(bus.target_export);

  bus.MEM_port(mem.target_export);
  bus.PERIPHERAL_port(peripheral.target_export);

  int ac1 = ac;
  char *av1[2];
  av1[0] = strdup(av[0]);
  av1[1] = strdup(av[1]);
	
  mips_proc1.init(ac, av);
  mips_proc2.init(ac1, av1);

  mips_proc1.set_prog_args();
  mips_proc2.set_prog_args();

  cerr << endl;

  sc_start();

  mips_proc1.PrintStat();
  mips_proc2.PrintStat();

  cerr << endl;

#ifdef AC_STATS
  mips1_proc1.ac_sim_stats.time = sc_simulation_time();
  mips1_proc1.ac_sim_stats.print();
#endif

#ifdef AC_DEBUG
  ac_close_trace();
#endif

  return mips_proc1.ac_exit_status + mips_proc2.ac_exit_status;
}
