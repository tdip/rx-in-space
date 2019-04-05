import { Observable, Observer, TeardownLogic } from "rxjs";

import { Context } from "./Context"
import { QuerySet } from "./QueryArgs";
import { OutputSet } from "./UpdateArgs";

/**
 * Interface that defines a link between two
 * values in the reactive graph of the
 * core signals framework.
 */
export interface ISignalsLinkBase{
    link(os: Observable<Context<any>[]>, output: Observer<any>[]): TeardownLogic;
}

export namespace ISignalsLink{

    export const Id: ISignalsLink = "id";

    export type Type = "id" | ISignalsLinkBase;
}

export type ISignalsLink = ISignalsLink.Type;

