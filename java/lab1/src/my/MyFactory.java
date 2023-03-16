package my;

import java.util.HashMap;
import java.util.Properties;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

/**
 * Uni
 */
public class MyFactory<ReturnObjectType> {
    private HashMap<String, Class<?>> map = new HashMap<String, Class<?>>();
    private final Properties cfg;
    
    public MyFactory(Properties cfg) {
        this.cfg = cfg;
    };
    public MyFactory(){
        cfg = null;
    };

    private void register(String k) throws ClassNotFoundException{
        //System.out.println(k);
        //System.out.flush();
        map.put(k, Class.forName(k));
    }

    private Constructor<?> getConstructors(String k, Object... args) throws ClassNotFoundException,
                                                                              NoSuchMethodException,
                                                                              SecurityException {
        String tmp = (cfg == null) ? k : cfg.getProperty(k);
        if (!map.containsKey(tmp)) {
            register(tmp);
        }
        
        Class<?>[] argsType = new Class[args.length];
        for (int i = 0; i < args.length; ++i) {
            argsType[i] = args[i].getClass();
        }
        return map.get(tmp).getConstructor(argsType);
    }

    public ReturnObjectType getObject(String k, Object ... args) throws InstantiationException,
                                                                        IllegalAccessException,
                                                                        IllegalArgumentException,
                                                                        InvocationTargetException, 
                                                                        ClassNotFoundException,
                                                                        NoSuchMethodException, 
                                                                        SecurityException  {
        var a = getConstructors(k, args);
        return (ReturnObjectType) a.newInstance();
    }


}