#ifdef NS3_MODULE_COMPILATION 
    error "Do not include ns3 module aggregator headers from other modules these are meant only for end user scripts." 
#endif 
#ifndef NS3_MODULE_CORE
    // Module headers: 
    #include <ns3/realtime-simulator-impl.h>
    #include <ns3/wall-clock-synchronizer.h>
    #include <ns3/int64x64-128.h>
    #include <ns3/unix-fd-reader.h>
    #include <ns3/system-mutex.h>
    #include <ns3/system-thread.h>
    #include <ns3/system-condition.h>
    #include <ns3/csv-reader.h>
    #include <ns3/event-garbage-collector.h>
    #include <ns3/random-variable-stream-helper.h>
    #include <ns3/abort.h>
    #include <ns3/ascii-file.h>
    #include <ns3/ascii-test.h>
    #include <ns3/assert.h>
    #include <ns3/attribute-accessor-helper.h>
    #include <ns3/attribute-construction-list.h>
    #include <ns3/attribute-container-accessor-helper.h>
    #include <ns3/attribute-container.h>
    #include <ns3/attribute-helper.h>
    #include <ns3/attribute.h>
    #include <ns3/boolean.h>
    #include <ns3/breakpoint.h>
    #include <ns3/build-profile.h>
    #include <ns3/calendar-scheduler.h>
    #include <ns3/callback.h>
    #include <ns3/command-line.h>
    #include <ns3/config.h>
    #include <ns3/default-deleter.h>
    #include <ns3/default-simulator-impl.h>
    #include <ns3/deprecated.h>
    #include <ns3/des-metrics.h>
    #include <ns3/double.h>
    #include <ns3/empty.h>
    #include <ns3/enum.h>
    #include <ns3/event-id.h>
    #include <ns3/event-impl.h>
    #include <ns3/fatal-error.h>
    #include <ns3/fatal-impl.h>
    #include <ns3/global-value.h>
    #include <ns3/hash-fnv.h>
    #include <ns3/hash-function.h>
    #include <ns3/hash-murmur3.h>
    #include <ns3/hash.h>
    #include <ns3/heap-scheduler.h>
    #include <ns3/int-to-type.h>
    #include <ns3/int64x64-double.h>
    #include <ns3/int64x64.h>
    #include <ns3/integer.h>
    #include <ns3/length.h>
    #include <ns3/list-scheduler.h>
    #include <ns3/log-macros-disabled.h>
    #include <ns3/log-macros-enabled.h>
    #include <ns3/log.h>
    #include <ns3/make-event.h>
    #include <ns3/map-scheduler.h>
    #include <ns3/math.h>
    #include <ns3/names.h>
    #include <ns3/node-printer.h>
    #include <ns3/nstime.h>
    #include <ns3/object-base.h>
    #include <ns3/object-factory.h>
    #include <ns3/object-map.h>
    #include <ns3/object-ptr-container.h>
    #include <ns3/object-vector.h>
    #include <ns3/object.h>
    #include <ns3/pair.h>
    #include <ns3/pointer.h>
    #include <ns3/priority-queue-scheduler.h>
    #include <ns3/ptr.h>
    #include <ns3/random-variable-stream.h>
    #include <ns3/ref-count-base.h>
    #include <ns3/rng-seed-manager.h>
    #include <ns3/rng-stream.h>
    #include <ns3/scheduler.h>
    #include <ns3/show-progress.h>
    #include <ns3/simple-ref-count.h>
    #include <ns3/simulation-singleton.h>
    #include <ns3/simulator-impl.h>
    #include <ns3/simulator.h>
    #include <ns3/singleton.h>
    #include <ns3/string.h>
    #include <ns3/synchronizer.h>
    #include <ns3/system-path.h>
    #include <ns3/system-wall-clock-ms.h>
    #include <ns3/system-wall-clock-timestamp.h>
    #include <ns3/test.h>
    #include <ns3/time-printer.h>
    #include <ns3/timer-impl.h>
    #include <ns3/timer.h>
    #include <ns3/trace-source-accessor.h>
    #include <ns3/traced-callback.h>
    #include <ns3/traced-value.h>
    #include <ns3/trickle-timer.h>
    #include <ns3/tuple.h>
    #include <ns3/type-id.h>
    #include <ns3/type-name.h>
    #include <ns3/type-traits.h>
    #include <ns3/uinteger.h>
    #include <ns3/unused.h>
    #include <ns3/valgrind.h>
    #include <ns3/vector.h>
    #include <ns3/watchdog.h>
#endif 