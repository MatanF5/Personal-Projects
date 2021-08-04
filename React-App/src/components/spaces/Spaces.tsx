import { Component } from "react";
import { Space } from "../../model/Model";
import { DataService } from "../../services/DataService";
import { SpaceComponent } from "./SpaceComponent";
import {ConfirmModelComponent} from './ConfirmModelComponent'

interface SpacesState {
    spaces: Space[],
    showModel: boolean,
    modelContent: string
}

interface SpacesProps {
    dataService: DataService
}

export class Spaces extends Component<SpacesProps, SpacesState> {

    constructor(props: SpacesProps) {
        super(props)
        this.state = {
            spaces: [],
            showModel: false,
            modelContent: ''
        }
        this.reserveSpace = this.reserveSpace.bind(this);
        this.closeModel = this.closeModel.bind(this);
    }

    async componentDidMount() {
        const spaces = await this.props.dataService.getSpaces();
        this.setState({
            spaces: spaces
        });
    }

    private async reserveSpace(spaceId: string) {
        const reservationResult = await this.props.dataService.reserveSpace(spaceId)
        if (reservationResult) {
            this.setState({
                showModel: true,
                modelContent: `You reserved the space with id ${spaceId} and got the reservation number ${reservationResult}`
            })
        } else {
            this.setState({
                showModel: true,
                modelContent: `You can't reserve the space with id ${spaceId}`
            })
        }
     }

    private renderSpaces() {
        const rows: any[] = []
        for (const space of this.state.spaces) {
            rows.push(
                <SpaceComponent
                    location={space.location}
                    name={space.name}
                    spaceId={space.spaceId}
                    reserveSpace={this.reserveSpace}
                />
            )
        }
        return rows;
    }
    private closeModel(){
        this.setState({
            showModel: false,
            modelContent: ''
        })
    }

    render() {
        return (
            <div>
                <h2>Welcome to the Spaces page!</h2>
                {this.renderSpaces()}
                <ConfirmModelComponent
                close = {this.closeModel}
                content = {this.state.modelContent}
                show = {this.state.showModel}
                />
            </div>
        )
    }


}