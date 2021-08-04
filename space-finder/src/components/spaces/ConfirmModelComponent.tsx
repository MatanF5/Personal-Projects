import { Component } from "react";


interface ConfirmModelComponentProps {
    show: boolean,
    content: string,
    close: () => void
}

export class ConfirmModelComponent extends Component<ConfirmModelComponentProps> {

    render() {
        if (!this.props.show) {
            return null
        } else {
            return <div className='model'>
                <div className='model-Content'>
                    <h2>You tried to reserve and ...</h2>
                    <h3 className='modelText'>{this.props.content}</h3>
                    <button  onClick={()=> this.props.close()} >Ok, close</button>
                </div>
            </div>
        }
    }

}