//////////////////////////////////////////////////////////////////
// Charles River Analytics, Inc., Cambridge, Massachusetts
//
// Copyright (C) 2016. All Rights Reserved.
// See http://www.cra.com or email info@cra.com for information. 
//////////////////////////////////////////////////////////////////
// Custom project or class-specific comments can go here. 
//////////////////////////////////////////////////////////////////

package com.cra.princess.monitor;

import com.cra.princess.core.OptimizableComponent;
import com.cra.princess.core.PrincessFeature;

import java.io.Serializable;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;

public class MonitorProxy<Env extends PrincessFeature, Input extends PrincessFeature, Output> implements InvocationHandler, Serializable {
  private final OptimizableComponent<Env, Input, Output> component;
  private ComponentMonitor<Env, Input, Output> monitor;

    /**
   * Comment for <code>serialVersionUID</code>
   */
  private static final long serialVersionUID = -8419938583872273502L;

    public MonitorProxy(OptimizableComponent<Env, Input, Output> component, ComponentMonitor<Env, Input, Output> monitor)
    {
      //this.monitor = MonitorControl.createMonitor(service);
      this.monitor = monitor;
      this.component = component;
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
      Object result;
      if (null != method && method.getName().equals("component")) {
        result = monitor.passToComponent(args);
      } else {
        result = method.invoke(component, args);
      }
      print(method, args, result);
      return result;
    }

    private void print(Method method, Object[] args, Object result)
    {
      System.out.println("-->Method : [" + method.getName() + "] ");
      System.out.println("-->Parameters : ");
      if (null != args) {
        for (Object object : args) {
          System.out.print("->" + object + " : ");
        }
      } else System.out.println("none");
      System.out.println("");

      System.out.println("-->Return : " + result);
    }
}
