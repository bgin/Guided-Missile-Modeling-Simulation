
#ifndef __GMS_HSW_CLIENT_METRICS_H__
#define __GMS_HSW_CLIENT_METRICS_H__ 1000050520201732


namespace {
  const unsigned int gGMS_HSW_CLIENT_METRICS_MAJOR = 1;
  const unsigned int gGMS_HSW_CLIENT_METRICS_MINOR = 0;
  const unsigned int gGMS_HSW_CLIENT_METRICS_MICRO = 0;
  const unsigned int gGMS_HSW_CLIENT_METRICS_FULLVER =
      1000U*gGMS_HSW_CLIENT_METRICS_MAJOR+
      100U*gGMS_HSW_CLIENT_METRICS_MINOR+
      10U*gGMS_HSW_CLIENT_METRICS_MICRO;
  const char * const pgGMS_HSW_CLIENT_METRICS_CREATION_DATE = "05-05-2020 17:36 +00200 (05 MAY 2020 5:36PM GMT+2)";
  const char * const pgGMS_HSW_CLIENT_METRICS_BUILD_DATE    = __DATE__ ":" __TIME__;
  const char * const pgGMS_HSW_CLIENT_METRICS_AUTHOR        = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
  const char * const pgGMS_HSW_CLIENT_METRICS_SYNOPSIS      = "Haswell client performance metrics based on TMA-Metrics (4.0)";
}

#include <cstdint.h>

namespace gms {

   const static uint32_t Issue_Width = 4;
   const static uint32_t Mem_L2_Store_Cost = 9;
   const static uint32_t Mem_L3_Weight = 7;
   const static uint32_t Energy_Unit = 61;
   const static uint32_t BAClear_Cost = 12;
   const static uint32_t MS_Switch_Cost = 2;
   const static uint32_t Avg_Assist_Cost = 100;
   const static uint32_t Mem_L3_Weight = 7;
   const static uint32_t Mem_STLB_Hit_Cost = 8;
   const static uint32_t Mem_XSNP_HitM_Cost = 60;
   const static uint32_t Mem_XSNP_Hit_Cost = 43;
   const static uint32_t Mem_XSNP_None_Cost = 29;


   // TMA Metrics.

   static inline
   uint64_t hsw_fetched_uops(const uint64_t idq_dsb_uops,
                         const uint64_t lsd_uops,
			 const idq_mite_uops,
			 const idq_ms_uops) {
        return (idq_dsb_uops +
	        lsd_uops     +
		idq_mite_uops +
		idq_ms_uops);
   }

   static inline
   uint64_t hsw_recovery_cycles(const uint64_t int_misc_recovery_cycles_any,
                            const uint64_t int_misc_recovery_cycles,
			    const bool is_ht_enabled) {
         return (is_ht_enabled ? int_misc_recovery_cycles_any/2ULL :
	                         int_misc_recovery_cycles);
   }

   static inline
   uint64_t hsw_execute_cycles(const uint64_t uops_executed_core_c1,
                           const bool is_ht_enabled) {
         return (is_ht_enabled ? uops_executed_core_c1 / 2ULL :
	                         uops_executed_core_c1);
   }

   static inline
   uint64_t hsw_sq_full_cycles(const uint64_t offcore_requests_buffer_sq_full,
                           const bool is_ht_enabled) {
         return (is_ht_enabled ? offcore_requests_buffer_sq_full / 2ULL :
	                         offcore_requests_buffer_sq_full);
   }

   static inline
   uint64_t hsw_itlb_miss_cycles(const uint64_t itlb_misses_stlb_hit,
                                 const uint64_t itlb_misses_walk_duration) {
         return (14ULL*itlb_misses_stlb_hit+itlb_misses_walk_duration);
   }

   static inline
   uint64_t hsw_frontend_rs_empty_cycles(const uint64_t rs_event_empty_cycles,
                                         const float frontend_latency) {
         return (frontend_latency<0.1f ? rs_event_empty_cycles :
	                                 0ULL);
   }

   static inline
   uint64_t hsw_cycles_0_ports_utilized(const uint64_t uops_executed_core_i1_c1,
                                        const uint64_t stalls_total,
					const uint64_t rs_event_empty_cycles,
					const float frontend_latency,
					const bool is_ht_enabled) {
         return (is_ht_enabled ? uops_executed_core_c1_i1/2ULL :
	                         stalls_total-hsw_frontend_rs_empty_cycles(rs_event_empty_cycles,frontend_latency));
   }

   static inline
   uint64_t hsw_cycles_1_ports_utilized(const uint64_t uops_executed_core_c1,
                                       const uint64_t uops_executed_core_c2,
				       const bool is_ht_enabled) {
         return (is_ht_enabled ? (uops_executed_core_c1-uops_executed_core_c2)/2ULL :
	                          uops_executed_core_c1-uops_executed_core_c2);
   }

   static inline
   uint64_t hsw_cycles_2_ports_utilized(const uint64_t uops_executed_core_c2,
                                            const uint64_t uops_executed_core_c3,
					    const bool is_ht_enabled) {
          return (is_ht_enabled ? (uops_executed_core_c2-uops_executed_core_c3)/2ULL :
	                           uops_executed_core_c2-uops_executed_core_c3);
   }

   static inline
   uint64_t hsw_cycles_3_ports_utilized(const uint64_t uops_executed_core_c3,
                                        const bool is_ht_enabled) {
          return (is_ht_enabled ? uops_executed_core_c3/2ULL :
	                          uops_executed_core_c3);
   }

#include <algorithm>

   static inline
   uint64_t hsw_frontend_latency_cycles(const uint64_t cpu_clk_unhalted_thread,
                                        const uint64_t idq_uops_not_delivered_cycles_0_uops_deliv_core) {
           return (std::min(cpu_clk_unhalted_thread,
	                    idq_uops_not_delivered_cycles_0_uops_deliv_core));
   }

   static inline
   uint64_t hsw_stalls_mem_any(const uint64_t cpu_clk_unhalted_thread,
                               const uint64_t cycles_activity_stalls_lm_pending) {
           return (std::min(cpu_clk_unhalted_thread,
	                    cycles_activity_stalls_lm_pending));
   }

   static inline
   uint64_t hsw_stalls_total(const uint64_t cpu_clk_unhalted_thread,
                             const uint64_t cycles_activity_cycles_no_execute) {
           return (std::min(cpu_clk_unhalted_thread,
	                    cycles_activity_cycles_no_execute));
   }
     
   
}









#endif /*__GMS_HSW_CLIENT_METRICS_H__*/
