/*
 * Copyright 2002-2016 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package io.pivotal.literx;

//generic imports to help with simpler IDEs (ie tech.io)
import java.util.*;
import java.util.function.*;
import java.time.*;

import java.util.concurrent.CompletableFuture;

import io.pivotal.literx.domain.User;
import io.reactivex.rxjava3.core.Flowable;
import io.reactivex.rxjava3.core.Observable;
import io.reactivex.rxjava3.core.Single;
import io.reactivex.rxjava3.core.BackpressureStrategy;
import org.reactivestreams.Publisher;
import reactor.core.publisher.Flux;
import reactor.core.publisher.Mono;

// https://tech.io/playgrounds/929/reactive-programming-with-reactor-3/Adapt

/**
 * Learn how to adapt from/to RxJava 3 Observable/Single/Flowable and Java 8+ CompletableFuture.
 *
 * Mono and Flux already implements Reactive Streams interfaces so they are natively
 * Reactive Streams compliant + there are {@link Mono#from(Publisher)} and {@link Flux#from(Publisher)}
 * factory methods.
 *
 * For RxJava 3, you should not use Reactor Adapter but only RxJava 3 and Reactor Core.
 *
 * @author Sebastien Deleuze
 */
public class Part09Adapt {

//========================================================================================

	// TODO Adapt Flux to RxJava Flowable
	// http://reactivex.io/RxJava/3.x/javadoc/io/reactivex/rxjava3/core/Flowable.html#fromPublisher-org.reactivestreams.Publisher-
	Flowable<User> fromFluxToFlowable(Flux<User> flux) {
		return Flowable.fromPublisher(flux);
	}

	// TODO Adapt RxJava Flowable to Flux
	// https://projectreactor.io/docs/core/release/api/reactor/core/publisher/Flux.html#from-org.reactivestreams.Publisher-
	Flux<User> fromFlowableToFlux(Flowable<User> flowable) {
		return Flux.from(flowable);
	}

//========================================================================================

	// TODO Adapt Flux to RxJava Observable
	Observable<User> fromFluxToObservable(Flux<User> flux) {
		return Observable.fromPublisher(flux);
	}

	// TODO Adapt RxJava Observable to Flux
	// http://reactivex.io/RxJava/3.x/javadoc/io/reactivex/rxjava3/core/Observable.html#toFlowable-io.reactivex.rxjava3.core.BackpressureStrategy-
	// http://reactivex.io/RxJava/3.x/javadoc/io/reactivex/rxjava3/core/BackpressureStrategy.html
	Flux<User> fromObservableToFlux(Observable<User> observable) {
		return Flux.from(observable.toFlowable(BackpressureStrategy.ERROR));
	}

//========================================================================================

	// TODO Adapt Mono to RxJava Single
	Single<User> fromMonoToSingle(Mono<User> mono) {
		return Observable.fromPublisher(mono).firstOrError();
	}

	// TODO Adapt RxJava Single to Mono
	Mono<User> fromSingleToMono(Single<User> single) {
		return Mono.from(single.toObservable().toFlowable(BackpressureStrategy.ERROR));
	}

//========================================================================================

	// TODO Adapt Mono to Java 8+ CompletableFuture
	CompletableFuture<User> fromMonoToCompletableFuture(Mono<User> mono) {
		return mono.toFuture();
	}

	// TODO Adapt Java 8+ CompletableFuture to Mono
	Mono<User> fromCompletableFutureToMono(CompletableFuture<User> future) {
		return Mono.fromFuture(future);
	}

}
